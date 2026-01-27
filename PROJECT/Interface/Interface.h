#pragma once
#include "../Evaluator/Evaluator.h"

class Interface {
public:
    Interface() = default;
    ~Interface() = default;
    void run(const std::string& file_name, int pop_size, double cross_prob, double mut_prob, int generations, const std::string& result_path);

private:
    Evaluator evaluator;
    std::string file_name;
};

