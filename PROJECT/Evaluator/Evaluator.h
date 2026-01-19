#pragma once
#include <string>

#include "../Instance/Instance.h"
#include "../Result/Result.hpp"
#include "../Error/Error.h"

class Evaluator {
public:
    Evaluator();
    explicit Evaluator(const std::string &file_name);
    ~Evaluator();
    Result<void, Error> loadFile(const std::string& file_name);
    double evaluate(Instance& instance) const;
    void saveToPython(Instance &instance, const std::string& filename) const;
    int getDepotId() const {return depot_id;}
    int getNumberOfTrucks() const {return number_of_trucks;}
    int getCapacity() const {return capacity;}
    int getDimension() const {return dimension;}
    double getDistance(int id_1, int id_2) const;
private:
    int depot_id;
    int number_of_trucks;
    int capacity;
    int dimension;
    std::vector<int> permutation;
    std::vector<std::pair<int, int>> nodes;
    std::vector<double> distances;
    void calculateDistances();
    std::vector<int> demands;
    struct TruckState {
        int previous_node_idx;
        double current_distance;
        int current_load;
        explicit TruckState(const int depot_id) : previous_node_idx(depot_id), current_distance(0.0), current_load(0) {}
    };
    mutable std::vector<TruckState> trucks;
};

