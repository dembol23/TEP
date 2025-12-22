#include "Instance.h"

#include <random>

Instance::Instance(const int nodes, const int number_of_groups) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, number_of_groups - 1);
    for (int i = 1; i < nodes; i++) {
        genotype.push_back(dist(rng));
    }
}

