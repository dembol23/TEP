cmake_minimum_required(VERSION 4.0)
project(PROJECT)

set(CMAKE_CXX_STANDARD 11)

add_executable(PROJECT main.cpp
        GeneticAlgorithm/GeneticAlgorithm.cpp
        GeneticAlgorithm/GeneticAlgorithm.h
        Instance/Instance.cpp
        Instance/Instance.h
        Evaluator/Evaluator.cpp
        Evaluator/Evaluator.h
        Result/Result.tpp
        Result/Result.hpp
        Error/Error.cpp
        Error/Error.h)
