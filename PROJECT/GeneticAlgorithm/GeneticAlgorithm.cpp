#include "GeneticAlgorithm.h"

#include <iostream>
#include <random>

GeneticAlgorithm::GeneticAlgorithm(const int &population_size, const double &cross_prob, const double &mutate_prob, const int &max_iterations, Evaluator &evaluator)
    :population_size(population_size),mutate_prob(mutate_prob), cross_prob(cross_prob), max_iterations(max_iterations), evaluator(&evaluator), rng(dev()){};

void GeneticAlgorithm::generate_population() {
    population.clear();
    const int dimension = evaluator->getDimension();
    const int groups = evaluator->getNumberOfTrucks();
    for (int i = 0; i < population_size; ++i) {
        SmartPointer<Instance> temp(new Instance(dimension, groups, rng));
        population.push_back(temp);
    }
}

SmartPointer<Instance> GeneticAlgorithm::selectBetter() {
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, population_size - 1);
    SmartPointer<Instance> i1(population[dist(rng)]);
    SmartPointer<Instance> i2(population[dist(rng)]);
    if (evaluator->evaluate(*i1) < evaluator->evaluate(*i2) ) return i1;
    return i2;
}

Result<SmartPointer<Instance>, Error> GeneticAlgorithm::run() {
    generate_population();
    SmartPointer<Instance> best_solution(nullptr);
    double best_fitness = std::numeric_limits<double>::max();
    int no_change = 0;
    const int number_of_trucks = evaluator->getNumberOfTrucks();
    for (int i = 0; i < max_iterations; ++i) {
        std::vector<SmartPointer<Instance>> new_population;
        if (!best_solution.isNull()) {
            new_population.push_back(best_solution);
        }
        while (new_population.size() < population_size) {
            const SmartPointer<Instance> parent1 = selectBetter();
            const SmartPointer<Instance> parent2 = selectBetter();

            std::pair<SmartPointer<Instance>, SmartPointer<Instance>> children = parent1->cross(&(*parent2), cross_prob);

            children.first->mutate(mutate_prob, number_of_trucks);
            children.second->mutate(mutate_prob, number_of_trucks);

            new_population.push_back(std::move(children.first));
            if (new_population.size() < population_size) {
                new_population.push_back(std::move(children.second));
            }
        }
        population = std::move(new_population);
        for (int k = 0; k < population_size; k++) {
            const double fit = evaluator->evaluate(*population[k]);
            if (fit < best_fitness) {
                best_fitness = fit;
                best_solution = population[k];
                no_change = 0;
            }
        }
        if (i % 1000 == 0) {
            std::cout << i << ": " << best_fitness << std::endl;
        }
        if (no_change++ >= 200000) break;
    }
    if (best_fitness < std::numeric_limits<double>::max() && !best_solution.isNull()) {
        return Result<SmartPointer<Instance>, Error>::success(best_solution);
    }
    return Result<SmartPointer<Instance>, Error>::fail(new Error("[ERROR] have not found best solution"));
}
