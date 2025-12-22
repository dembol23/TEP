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
    Result<void, Error> loadFile(std::string file_name);
    double evaluate(const Instance& instance);
    int getDepotId() const {return depot_id;}
    int getNumberOfGroups() const {return number_of_groups;}
    int getCapacity() const {return capacity;}
    int getDimension() const {return dimension;}
private:
    int depot_id;
    int number_of_groups;
    int capacity;
    int dimension;
    std::vector<std::pair<int, int>> nodes;
    std::vector<int> demands;
    double calculateDistance(int i, int j);
};

