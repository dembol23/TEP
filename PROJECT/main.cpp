#include <iostream>
#include "Evaluator/Evaluator.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"

int main() {
    Evaluator evaluator;
    Result<void, Error> result = evaluator.loadFile("../lcvrp/Vrp-Set-A/A-n32-k5.lcvrp");

    if (result.isSuccess()) {
        std::cout << "Plik wczytany poprawnie." << std::endl;
        std::cout << "Liczba miast (Dimension): " << evaluator.getDimension() << std::endl;
        std::cout << "Liczba ciężarówek (k): " << evaluator.getNumberOfTrucks() << std::endl;
        std::cout << "Depot id: " << evaluator.getDepotId() << std::endl;

        constexpr int popSize = 300;
        constexpr double crossProb = 0.85;
        constexpr double mutProb = 0.015;
        constexpr int generations = 10000;

        GeneticAlgorithm ga(popSize, crossProb, mutProb, generations, evaluator);
        Result<SmartPointer<Instance>, Error> result11 = ga.run();
        if (result11.isSuccess()) {
            std::cout << "Najlepszy genotyp: " << result11.getValue()->genotypeToString() << std::endl;
            std::cout << "Najlepszy fitness: " << result11.getValue()->getFitness() << std::endl;
            evaluator.saveToPython(*result11.getValue(), "plot_solution.py");
        }
        else {
            std::cout << result11.errorsToString();
        }

    } else {
        std::cout << result.errorsToString() << std::endl;
    }


    return 0;
}