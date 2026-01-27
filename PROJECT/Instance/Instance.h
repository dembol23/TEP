#pragma once
#include <random>
#include <vector>

#include "../../L5/SmartPointer/SmartPointer.h"

class Instance {
public:
    explicit Instance(int nodes, int number_of_groups, std::mt19937 &rng);
    explicit Instance(const std::vector<int> &genotype, std::mt19937 &rng);
    bool isEvaluated() const {return fitness != -1;};
    double getFitness() const {return fitness;};
    void setFitness(const double fit) {fitness = fit;};
    std::vector<int> mutate(double mutate_prob,int number_of_groups);
    std::pair<SmartPointer<Instance>, SmartPointer<Instance>> cross(const Instance* other, double cross_prob) const;
    std::vector<int> getGenotype() {return genotype;};
    std::string genotypeToString() const;
private:
    std::vector<int> genotype;
    double fitness;
    std::mt19937* rng;
};


