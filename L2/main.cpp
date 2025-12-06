#include <iostream>
#include <ostream>

#include "Number.h"

int main() {
    Number number = Number(-9);
    --number;
    std::cout << "Numer: " << number.toString() << std::endl;
    number = number + 20;
    std::cout << "Numer: " << number.toString() << std::endl;

    Number number1 = Number(-10);
    Number number2 = Number(-21);
    std::cout << "Numer 1: " << number1.toString() << std::endl;
    std::cout << "Numer 2: " << number2.toString() << std::endl;

    Number result = number1 + number2;
    std::cout << "Dodawanie: " << result.toString() << std::endl;
    Number result2 = number1 - number2;
    std::cout << "Odejmowanie: " << result2.toString() << std::endl;
    Number result3 = number1 * number2;
    std::cout << "Mnożenie: " << result3.toString() << std::endl;
    try {
        Number result4 = number1 / number2;
        std::cout << "Dzielenie: " << result4.toString() << std::endl;
    }
    catch (std::invalid_argument &err) {
        std::cout << err.what() << std::endl;
    }
}
