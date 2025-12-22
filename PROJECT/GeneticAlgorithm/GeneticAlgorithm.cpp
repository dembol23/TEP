#include "GeneticAlgorithm.h"

#include <iostream>
#include <random>

GeneticAlgorithm::GeneticAlgorithm(const int &population_size, const double &cross_prob, const double &mutate_prob, const int &max_iterations, Evaluator &evaluator)
    :population_size(population_size),mutate_prob(mutate_prob), cross_prob(cross_prob), max_iterations(max_iterations), evaluator(&evaluator){};

void GeneticAlgorithm::generate_population() {
    population.clear();
    const int dimension = evaluator->getDimension();
    const int groups = evaluator->getNumberOfGroups();
    for (int i = 0; i < population_size; ++i) {
        SmartPointer<Instance> temp(new Instance(dimension, groups));
        population.push_back(temp);
    }
}

SmartPointer<Instance> GeneticAlgorithm::selectBetter() {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, population_size - 1);
    SmartPointer<Instance> i1(population[dist(rng)]);
    SmartPointer<Instance> i2(population[dist(rng)]);
    if (evaluator->evaluate(*i1) < evaluator->evaluate(*i2) ) return i1; // im mniej tym lepiej
    return i2;
}

void GeneticAlgorithm::run() {
    generate_population();
    SmartPointer<Instance> best_solution(nullptr);
    double best_fitness = std::numeric_limits<double>::max();
    const int number_of_groups = evaluator->getNumberOfGroups();
    for (int i = 0; i < max_iterations; ++i) {
        std::vector<SmartPointer<Instance>> new_population;

        while (new_population.size() < population_size) {
            SmartPointer<Instance> parent1 = selectBetter();
            SmartPointer<Instance> parent2 = selectBetter();

            std::pair<SmartPointer<Instance>, SmartPointer<Instance>> children = parent1->cross(&(*parent2), cross_prob);

            children.first->mutate(mutate_prob, number_of_groups);
            children.second->mutate(mutate_prob, number_of_groups);

            new_population.push_back(children.first);
            if (new_population.size() < population_size) {
                new_population.push_back(children.second);
            }
        }
        population = new_population;
        for (int k = 0; k < population_size; k++) {
            const double fit = evaluator->evaluate(*population[k]);
            if (fit < best_fitness) {
                best_fitness = fit;
                best_solution = SmartPointer<Instance>(new Instance(population[k]->getGenotype()));
            }
        }
        if (i % 100 == 0) {
            std::cout << "Generacja " << i << " | Najlepszy wynik: " << best_fitness << std::endl;
        }
    }
    std::cout << "--- KONIEC ---" << std::endl;
    std::cout << "Znaleziony najlepszy koszt: " << best_fitness << std::endl;

    std::cout << "Najlepsza trasa (genotyp): ";
    std::vector<int> bestGeno = best_solution->getGenotype();
    for(int g : bestGeno) std::cout << g << " ";
    std::cout << std::endl;
}
