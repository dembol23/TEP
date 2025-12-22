#pragma once
#include <vector>

#include "../../L5/SmartPointer/SmartPointer.h"

class Instance {
public:
    explicit Instance(int nodes, int number_of_groups);
    explicit Instance(const std::vector<int> &genotype);
    double calcFitness();
    std::vector<int> mutate(double mutate_prob,int number_of_groups);
    std::pair<SmartPointer<Instance>, SmartPointer<Instance>> cross(Instance* other, double cross_prob);
    std::vector<int> getGenotype() {return genotype;};
private:
    std::vector<int> genotype;
};


