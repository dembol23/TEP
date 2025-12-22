#include "Instance.h"

#include <random>

Instance::Instance(const int nodes, const int number_of_groups) {
    for (int i = 1; i < nodes; i++) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(1,number_of_groups);
        genotype.push_back(dist(rng));
    }
}

