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
    int getCapacity() const {return capacity;}
    int getDimension() const {return dimension;}
private:
    int capacity;
    int dimension;
    std::vector<std::pair<int, int>> nodes;
    std::vector<int> demands;
    double calculateDistance(int i, int j);
};

