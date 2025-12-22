#include "Evaluator.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

Evaluator::Evaluator() : capacity(0), dimension(0), number_of_groups(0), depot_id(0) {}

Evaluator::Evaluator(const std::string &file_name) {
    capacity = 0;
    dimension = 0;
    number_of_groups = 0;
    loadFile(file_name);
}

Evaluator::~Evaluator() {}

Result<void, Error> Evaluator::loadFile(std::string file_name) {
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
            }
            else if (line.find("CAPACITY") != std::string::npos) {
                std::string trash;
                ss >> keyword >> trash >> capacity;
            }
            else if (line.find("COMMENT") != std::string::npos) {
                std::string phrase = "No of trucks:";
                size_t pos = line.find(phrase);
                if (pos != std::string::npos) {
                    std::stringstream ss_trucks(line.substr(pos + phrase.length()));
                    ss_trucks >> number_of_groups;
                }
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
                    int id, x, y;
                    if (ss >> id >> x >> y) {
                        nodes.push_back(std::make_pair(x, y));
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
                            depot_id = id;
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
    return Result<void, Error>::success();
}

double Evaluator::calculateDistance(const int id_1, const int id_2) const {
    if (id_1 == id_2) {
        return 0.0;
    }
    const std::pair<int, int>& node_1 = nodes[id_1 - 1];
    const std::pair<int, int>& node_2 = nodes[id_2 - 1];
    const double distance = sqrt(pow(node_1.first - node_2.first, 2) + pow(node_1.second - node_2.second, 2));
    return distance;
}

double Evaluator::evaluate(Instance& instance) const {
    const std::vector<int>& genotype = instance.getGenotype();
    std::vector<std::vector<int>> truck_routes(number_of_groups);

    for (int i = 0; i < genotype.size(); i++) {
        const int truck_id = genotype[i];
        int client_id = i + 1;
        if (i >= depot_id - 1) {
            client_id++;
        }
        truck_routes[truck_id].push_back(client_id);
    }

    double total_distance = 0.0;

    for (int i = 0; i < number_of_groups; i++) {
        if (truck_routes[i].empty()) continue;
        double current_distance = 0.0;
        int previous_id = depot_id;
        for (const int j : truck_routes[i]) {
            current_distance += calculateDistance(previous_id, j);
            previous_id = j;
        }
        current_distance += calculateDistance(previous_id, depot_id);
        total_distance += current_distance;
    }

    return total_distance;
}