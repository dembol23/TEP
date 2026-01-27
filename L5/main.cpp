#include <iostream>
#include "SmartPointer/SmartPointer.h"
#include "BorrowingPointer/BorrowingPointer.h"
#include "../L4/Tree/Tree.h"

int main() {
    std::cout << "=== TEST 1: Budowanie drzewa ===" << std::endl;
    Tree tree1;
    tree1.enter("+ a * b 5");
    std::cout << "Drzewo 1: " << tree1.print() << std::endl;

    std::cout << "\n=== TEST 2: Kopiowanie (operator=) ===" << std::endl;
    std::cout << "Oczekiwane: Seria komunikatow '--- COPY Node...'" << std::endl;
    Tree tree2 = tree1; // Tu zachodzi GŁĘBOKA KOPIA
    std::cout << "Drzewo 2 (kopia): " << tree2.print() << std::endl;

    std::cout << "\n=== TEST 3: Przenoszenie (std::move) ===" << std::endl;
    std::cout << "Oczekiwane: BRAK komunikatow '--- COPY Node...' (0 kopii)" << std::endl;
    Tree tree3;
    tree3 = std::move(tree1); // Tu zachodzi PRZENIESIENIE (kradzież root)
    std::cout << "Drzewo 3 (przeniesione): " << tree3.print() << std::endl;

    std::cout << "Drzewo 1 (po przeniesieniu powinno byc puste lub zniszczone): '"
              << tree1.print() << "'" << std::endl;

    std::cout << "\n=== TEST 4: Sumowanie drzew (operator+) ===" << std::endl;
    Tree sumTree = tree2 + tree3;
    std::cout << "Suma: " << sumTree.print() << std::endl;




    BorrowingPointer<int>* bp = nullptr;


    {
        SmartPointer<int> sp1(new int(100));
        bp = new BorrowingPointer<int>(sp1.borrow());
        {
            SmartPointer<int> sp2(sp1);
            std::cout << "Wartosc BP: " << *(*bp) << std::endl;
        }
        if (bp->get() == nullptr) {
            std::cout << "1bp wygasl" << std::endl;
        } else {
            std::cout << "1bp nie wygasl" << std::endl;
        }
    }
    if (bp->get() == nullptr) {
        std::cout << "2bp wygasl" << std::endl;
    } else {
        std::cout << "2bp nie wygasl" << std::endl;
    }


    delete bp;
    return 0;
}