#pragma once
#include "../Evaluator/Evaluator.h"
#include "../Instance/Instance.h"

class GeneticAlgorithm {
public:
    GeneticAlgorithm(const int &population_size, const double &cross_prob, const double &mutate_prob, const int &max_iterations, Evaluator &evaluator);
    Result<SmartPointer<Instance>, Error> run();
private:
    int population_size;
    double mutate_prob;
    double cross_prob;
    int max_iterations;
    std::vector<SmartPointer<Instance>> population;
    Evaluator* evaluator;
    void generate_population();
    SmartPointer<Instance> selectBetter();
    std::random_device dev;
    std::mt19937 rng;
};


