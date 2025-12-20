#include <iostream>
#include <ostream>

#include "SmartPointer/SmartPointer.h"
int main() {
    int* a = new int(10);
    SmartPointer<int> test1(a);
    SmartPointer<int> test2(test1);
    std::cout << test1.getRefCounter() << std::endl;
    std::cout << test2.getRefCounter() << std::endl;
    int b = *test1;
    std::cout << "b: " << b << std::endl;
    std::cout << "a: " << *a << std::endl;
}