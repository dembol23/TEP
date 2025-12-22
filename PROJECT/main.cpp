#include <iostream>

#include "Evaluator/Evaluator.h"

int main() {
    Evaluator test{};
    Result<void, Error> result = test.loadFile("../Test_Files/test.vrp");
    if (result.isSuccess()) {
        std::cout << test.getCapacity() << std::endl;
        std::cout << test.getDimension() << std::endl;
    }
    else {
        std::cout << result.errorsToString() << std::endl;
    }
    return 0;
}
