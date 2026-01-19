#include "Instance.h"

#include <random>

Instance::Instance(const std::vector<int> &genotype, std::mt19937 &rng):genotype(genotype), fitness(-1), rng(&rng) {};

Instance::Instance(const int nodes, const int number_of_groups, std::mt19937 &rng):fitness(-1) {
    this->rng = &rng;
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, number_of_groups - 1);
    for (int i = 1; i < nodes; i++) {
        genotype.push_back(dist(rng));
    }
}

std::vector<int> Instance::mutate(const double mutate_prob, const int number_of_groups) {
    std::uniform_real_distribution<> dist_prob(0.0, 1.0);
    std::uniform_int_distribution<> dist_truck(0, number_of_groups - 1);

    bool modified = false;
    for (int & i : genotype) {
        if (dist_prob(*rng) < mutate_prob) {
            i = dist_truck(*rng);
            modified = true;
        }
    }
    if (modified) setFitness(-1);
    return genotype;
}

std::pair<SmartPointer<Instance>, SmartPointer<Instance>> Instance::cross(const Instance* other, double cross_prob) const {
    std::uniform_real_distribution<> dist_prob(0.0, 1.0);
    SmartPointer<Instance> child_1(new Instance(genotype, *this->rng));
    SmartPointer<Instance> child_2(new Instance(other->genotype, *this->rng));
    if (dist_prob(*rng) < cross_prob) {
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, genotype.size() - 1);
        const int split_index = dist(*rng);
        for (int i = split_index; i < genotype.size(); i++) {
            std::swap(child_1->genotype[i], child_2->genotype[i]);
        }
    }
    return std::make_pair(child_1,child_2);
}

std::string Instance::genotypeToString() const {
    std::string result;
    for (const int i : genotype) {
        result += std::to_string(i);
    }
    return result;
}
