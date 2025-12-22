#include "Instance.h"

#include <random>

Instance::Instance(const std::vector<int> &genotype):genotype(genotype){};

Instance::Instance(const int nodes, const int number_of_groups) {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, number_of_groups - 1);
    for (int i = 1; i < nodes; i++) {
        genotype.push_back(dist(rng));
    }
}

std::vector<int> Instance::mutate(const double mutate_prob, const int number_of_groups) {
    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_real_distribution<> dist_prob(0.0, 1.0);
    std::uniform_int_distribution<> dist_truck(0, number_of_groups - 1);

    for (int & i : genotype) {
        if (dist_prob(rng) < mutate_prob) {
            i = dist_truck(rng);
        }
    }
    return genotype;
}

std::pair<SmartPointer<Instance>, SmartPointer<Instance>> Instance::cross(Instance* other, double cross_prob) {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist_prob(0.0, 1.0);
    SmartPointer<Instance> child_1(new Instance(genotype));
    SmartPointer<Instance> child_2(new Instance(other->genotype));
    if (dist_prob(rng) < cross_prob) {
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, genotype.size() - 1);
        int split_index = dist(rng);
        for (int i = split_index; i < genotype.size(); i++) {
            std::swap(child_1->genotype[i], child_2->genotype[i]);
        }
    }
    return std::make_pair(child_1,child_2);
}