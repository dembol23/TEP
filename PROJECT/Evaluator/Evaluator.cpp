#include "Evaluator.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iostream>

Evaluator::Evaluator(): depot_id(0), number_of_trucks(0), capacity(0), dimension(0) {}

Evaluator::Evaluator(const std::string &file_name) {
    depot_id = 0;
    capacity = 0;
    dimension = 0;
    number_of_trucks = 0;
    loadFile(file_name);
}

Evaluator::~Evaluator() = default;

Result<void, Error> Evaluator::loadFile(const std::string& file_name) {
    std::ifstream file(file_name);

    if (!file.is_open()) {
        return Result<void, Error>::fail(new Error("[FILE ERROR] file not found for path: " + file_name));
    }

    std::string line;
    std::string section;
    bool skip_line = false;

    while (std::getline(file, line)) {
        if (line.empty()) {
            skip_line = true;
        }

        if (!skip_line) {
            std::stringstream ss(line);
            std::string keyword;

            if (line.find("DIMENSION") != std::string::npos) {
                std::string trash;
                ss >> keyword >> trash >> dimension;
                if (dimension <= 0) {
                    return Result<void, Error>::fail(new Error("[FILE ERROR] dimension in file is equal or less than 0: " + file_name));
                }
                nodes.reserve(dimension);
                demands.reserve(dimension);
                permutation.reserve(dimension - 1);
            }
            else if (line.find("CAPACITY") != std::string::npos) {
                std::string trash;
                ss >> keyword >> trash >> capacity;
            }
            else if (line.find("NAME") != std::string::npos) {
                std::string phrase = "-k";
                size_t pos = line.find(phrase);
                if (pos != std::string::npos) {
                    std::stringstream ss_trucks(line.substr(pos + phrase.length()));
                    ss_trucks >> number_of_trucks;
                }
            }
            else if (line.find("PERMUTATION") != std::string::npos) {
                std::string trash;
                ss >> keyword >> trash;

                int id;
                while (ss >> id) {
                    permutation.push_back(id - 1);
                }
                skip_line = true;
            }
            else if (line.find("NODE_COORD_SECTION") != std::string::npos) {
                section = "COORD";
                skip_line = true;
            }
            else if (line.find("DEMAND_SECTION") != std::string::npos) {
                section = "DEMAND";
                skip_line = true;
            }
            else if (line.find("DEPOT_SECTION") != std::string::npos) {
                section = "DEPOT";
                skip_line = true;
            }
            else if (line.find("EOF") != std::string::npos) {
                skip_line = true;
            }

            if (!skip_line) {
                if (section == "COORD") {
                    int id;
                    double x, y;
                    if (ss >> id >> x >> y) {
                        nodes.emplace_back(x, y);
                    }
                    else {
                        return Result<void, Error>::fail(new Error("[FILE ERROR] could not parse section: " + section));
                    }
                }
                else if (section == "DEMAND") {
                    int id, demand;
                    if (ss >> id >> demand) {
                        demands.push_back(demand);
                    }
                    else {
                        return Result<void, Error>::fail(new Error("[FILE ERROR] could not parse section: " + section));
                    }
                }
                else if (section == "DEPOT") {
                    int id;
                    if (ss >> id) {
                        if (id != -1) {
                            depot_id = id - 1;
                        } else {
                            section = "";
                        }
                    }
                    else {
                        return Result<void, Error>::fail(new Error("[FILE ERROR] could not parse section: " + section));
                    }
                }
            }
        }
        skip_line = false;
    }
    file.close();

    if (nodes.size() != dimension) {
        return Result<void, Error>::fail(new Error("[FILE ERROR] loaded nodes count does not match DIMENSION"));
    }
    if (demands.size() != dimension) {
        return Result<void, Error>::fail(new Error("[FILE ERROR] loaded demands count does not match DIMENSION"));
    }
    if (permutation.size() != dimension - 1) {
        return Result<void, Error>::fail(new Error("[FILE ERROR] loaded permutation sequence count does not match DIMENSION"));
    }
    calculateDistances();
    if (number_of_trucks > 0) {
        trucks.assign(number_of_trucks, TruckState(depot_id));
    }
    return Result<void, Error>::success();
}

double Evaluator::evaluate(Instance& instance) const {
    if (instance.getFitness() != -1) return instance.getFitness();

    const std::vector<int>& genotype = instance.getGenotype();
    double total_distance = 0.0;
    for (auto& truck : trucks) {
        truck.previous_node_idx = depot_id;
        truck.current_load = 0;
        truck.current_distance = 0.0;
    }
    const double PENALTY_MULTIPLIER = 100.0;

    for (const int client_idx : permutation){
        const int truck_idx = genotype[client_idx - 1];
        TruckState& truck = trucks[truck_idx];
        truck.current_distance += getDistance(truck.previous_node_idx, client_idx);
        truck.current_load += demands[client_idx];
        truck.previous_node_idx = client_idx;
    }

    for (const TruckState& truck : trucks) {
        double route_distance = truck.current_distance;
        route_distance += getDistance(truck.previous_node_idx, depot_id);
        if (truck.current_load > capacity) {
            const int overweight = truck.current_load - capacity;
            route_distance += overweight * PENALTY_MULTIPLIER;
        }
        total_distance += route_distance;
    }

    instance.setFitness(total_distance);
    return total_distance;
}

void Evaluator::calculateDistances() {
    distances.resize(dimension*dimension);

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i == j) distances[i * dimension + j] = 0.0;
            else {
                const double dx = nodes[i].first - nodes[j].first;
                const double dy = nodes[i].second - nodes[j].second;
                distances[i * dimension + j] = std::sqrt(dx*dx + dy*dy);
            }
        }
    }
}

double Evaluator::getDistance(const int id_1, const int id_2) const {
    return distances[id_1 * dimension + id_2];
}

void Evaluator::saveToPython(Instance& instance, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "import matplotlib.pyplot as plt\n\n";
    file << "def plot_routes():\n";
    file << "    # Współrzędne (x, y)\n";
    file << "    coords = {\n";
    for (int i = 0; i < nodes.size(); i++) {
        file << "        " << i + 1 << ": (" << nodes[i].first << ", " << nodes[i].second << "),\n";
    }
    file << "    }\n\n";
    file << "    # Zapotrzebowanie (demand)\n";
    file << "    demands = {\n";
    for (int i = 0; i < demands.size(); i++) {
        file << "        " << i + 1 << ": " << demands[i] << ",\n";
    }
    file << "    }\n\n";
    file << "    plt.figure(figsize=(12, 10))\n";
    int python_depot_key = depot_id + 1;
    file << "    plt.plot(coords[" << python_depot_key << "][0], coords[" << python_depot_key << "][1], 'rs', markersize=12, label='Depot', zorder=10)\n";
    file << "    for i in coords:\n";
    file << "        if i != " << python_depot_key << ":\n";
    file << "            plt.plot(coords[i][0], coords[i][1], 'bo', markersize=6, zorder=5)\n";
    file << "        plt.text(coords[i][0], coords[i][1], f'{i}\\n[{demands[i]}]', fontsize=8, ha='center', va='bottom', zorder=15)\n\n";

    const std::vector<int>& genotype = instance.getGenotype();
    std::vector<std::vector<int>> truck_routes(number_of_trucks);

    for (const int node_idx : permutation) {
        int gene_idx = node_idx - 1;

        if (gene_idx >= 0 && gene_idx < genotype.size()) {
            int truck_id = genotype[gene_idx];
            truck_routes[truck_id].push_back(node_idx + 1);
        }
    }

    std::string colors[] = {"'b'", "'g'", "'c'", "'m'", "'y'", "'k'", "'orange'", "'purple'"};
    for (int i = 0; i < number_of_trucks; i++) {
        if (truck_routes[i].empty()) continue;
        std::string color = colors[i % 8];
        file << "    # Trasa " << i+1 << "\n";
        file << "    x = [coords[" << python_depot_key << "][0]]\n";
        file << "    y = [coords[" << python_depot_key << "][1]]\n";
        for (int client : truck_routes[i]) {
            file << "    x.append(coords[" << client << "][0])\n";
            file << "    y.append(coords[" << client << "][1])\n";
        }
        file << "    x.append(coords[" << python_depot_key << "][0])\n";
        file << "    y.append(coords[" << python_depot_key << "][1])\n";
        file << "    plt.plot(x, y, " << color << ", linestyle='-', linewidth=1.5, alpha=0.7, label='Trasa " << i+1 << "')\n";
    }
    file << "\n    plt.title('Wizualizacja VRP - Fitness: " << instance.getFitness() << "')\n";
    file << "    plt.legend(loc='upper left', bbox_to_anchor=(1, 1))\n";
    file << "    plt.tight_layout()\n";
    file << "    plt.grid(True, linestyle='--', alpha=0.5)\n";
    file << "    plt.show()\n\n";
    file << "if __name__ == '__main__':\n";
    file << "    plot_routes()\n";

    file.close();
}