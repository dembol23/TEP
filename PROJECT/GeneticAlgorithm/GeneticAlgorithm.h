#pragma once
#include "../Instance/Instance.h"

class GeneticAlgorithm {
public:
    GeneticAlgorithm();
    ~GeneticAlgorithm();
    GeneticAlgorithm(int popSize, double crossProb, double mutProb);
    void run();
private:
    int population_size;
    double mutate_prob;
    double cross_prob;
    std::vector<SmartPointer<Instance>> population;
};


