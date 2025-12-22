#include <iostream>
#include "Evaluator/Evaluator.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"

int main() {
    Evaluator evaluator;
    Result<void, Error> result = evaluator.loadFile("../Test_Files/A-n32-k5.vrp");

    if (result.isSuccess()) {
        std::cout << "Plik wczytany poprawnie." << std::endl;
        std::cout << "Liczba miast (Dimension): " << evaluator.getDimension() << std::endl;
        std::cout << "Liczba ciężarówek (k): " << evaluator.getNumberOfGroups() << std::endl;
        std::cout << "Depot id: " << evaluator.getDepotId() << std::endl;

        constexpr int popSize = 100;      // Wielkość populacji
        constexpr double crossProb = 0.6; // Szansa krzyżowania 60%
        constexpr double mutProb = 0.05;  // Szansa mutacji 5%
        constexpr int generations = 10000; // Ile razy pętla ma obrócić

        GeneticAlgorithm ga(popSize, crossProb, mutProb, generations, evaluator);
        ga.run();

    } else {
        std::cout << result.errorsToString() << std::endl;
    }

    return 0;
}