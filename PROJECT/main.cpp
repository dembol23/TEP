#include "Interface/Interface.h"

int main() {
    Interface *interface = new Interface();
    const int popSize = 300;
    const double crossProb = 0.85;
    const double mutProb = 0.015;
    const int generations = 20000;
    interface->run("../lcvrp/Vrp-Set-A/A-n32-k5.lcvrp", popSize, crossProb, mutProb, generations, "/Users/wiktordembny/Pliki/testy/plot_solution.py");

    return 0;
}