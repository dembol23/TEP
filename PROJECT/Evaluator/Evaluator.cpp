#include "Evaluator.h"

#include <fstream>
#include <sstream>

Evaluator::Evaluator():capacity(0),dimension(0) {}

Evaluator::Evaluator(const std::string &file_name) {
    loadFile(file_name);
}

Evaluator::~Evaluator() {}

double Evaluator::calculateDistance(int i, int j) {

}

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
                }
                else if (section == "DEMAND") {
                    int id, demand;
                    if (ss >> id >> demand) {
                        demands.push_back(demand);
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
