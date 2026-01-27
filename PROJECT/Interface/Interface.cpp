#include "Interface.h"
#include "../GeneticAlgorithm/GeneticAlgorithm.h"

#include <iostream>

void Interface::run(const std::string& file_name, const int pop_size, const double cross_prob, const double mut_prob, const int generations, const std::string& result_path) {
    Result<void, Error> result = evaluator.loadFile(file_name);

    if (result.isSuccess()) {
        std::cout << "Plik wczytany poprawnie." << std::endl;
        std::cout << "Liczba miast (Dimension): " << evaluator.getDimension() << std::endl;
        std::cout << "Liczba ciężarówek (k): " << evaluator.getNumberOfTrucks() << std::endl;
        std::cout << "Depot id: " << evaluator.getDepotId() << std::endl;

        GeneticAlgorithm ga(pop_size, cross_prob, mut_prob, generations, evaluator);
        Result<SmartPointer<Instance>, Error> result11 = ga.run();
        if (result11.isSuccess()) {
            std::cout << "Najlepszy genotyp: " << result11.getValue()->genotypeToString() << std::endl;
            std::cout << "Najlepszy fitness: " << result11.getValue()->getFitness() << std::endl;
            evaluator.saveToPython(*result11.getValue(), result_path);
        }
        else {
            std::cout << result11.errorsToString();
        }

    } else {
        std::cout << result.errorsToString() << std::endl;
    }
}

