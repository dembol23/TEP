#include <iostream>
#include <ostream>

#include "../L4/Result/Result.hpp"
#include "../L4/Error/Error.h"
#include "../L4/Tree/Tree.h"

#include "SmartPointer/SmartPointer.h"
int main() {
    // int* a = new int(10);
    // SmartPointer<int> test1(a);
    // SmartPointer<int> test2(test1);
    // std::cout << test1.getRefCounter() << std::endl;
    // std::cout << test2.getRefCounter() << std::endl;
    // int b = *test1;
    // std::cout << "b: " << b << std::endl;
    // std::cout << "a: " << *a << std::endl;


    std::cout << "=== TEST 1: Budowanie drzewa ===" << std::endl;
    Tree tree1;
    // Formuła: a + b * 5
    tree1.enter("+ a * b 5");
    std::cout << "Drzewo 1: " << tree1.print() << std::endl;

    std::cout << "\n=== TEST 2: Kopiowanie (operator=) ===" << std::endl;
    std::cout << "Oczekiwane: Seria komunikatow '--- COPY Node...'" << std::endl;
    Tree tree2 = tree1; // Tu zachodzi GŁĘBOKA KOPIA
    std::cout << "Drzewo 2 (kopia): " << tree2.print() << std::endl;

    std::cout << "\n=== TEST 3: Przenoszenie (std::move) ===" << std::endl;
    std::cout << "Oczekiwane: BRAK komunikatow '--- COPY Node...' (0 kopii)" << std::endl;
    Tree tree3 = std::move(tree1); // Tu zachodzi PRZENIESIENIE (kradzież root)
    std::cout << "Drzewo 3 (przeniesione): " << tree3.print() << std::endl;

    std::cout << "Drzewo 1 (po przeniesieniu powinno byc puste lub zniszczone): '"
              << tree1.print() << "'" << std::endl;

    std::cout << "\n=== TEST 4: Sumowanie drzew (operator+) ===" << std::endl;
    Tree sumTree = tree2 + tree3;
    std::cout << "Suma: " << sumTree.print() << std::endl;
}