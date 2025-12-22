#include <iostream>
#include <random>

#include "Evaluator/Evaluator.h"

int main() {
    Evaluator test{};
    Result<void, Error> result = test.loadFile("../Test_Files/A-n32-k5.vrp");
    if (!result.isSuccess()) {
        std::cout << result.errorsToString() << std::endl;
    }
    else {
        Instance t(test.getDimension(), test.getNumberOfGroups());
        std::vector<int> v = t.getGenotype();
        for (int i = 0; i < v.size(); i++) {
            std::cout << v[i] << std::endl;
        }
    }
    return 0;
}
