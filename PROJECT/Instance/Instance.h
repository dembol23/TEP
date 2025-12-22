#pragma once
#include <vector>

class Instance {
public:
    Instance();
    Instance(const Instance& instance);
    ~Instance();
    Instance& operator=(const Instance& instance);
    explicit Instance(std::vector<int> genotype);
    double calcFitness();
    std::vector<int> mutate(double mutate_prob);
    std::pair<Instance, Instance> cross(const Instance& other, double cross_prob);
private:
    std::vector<int> genotype;
};


