#include <iostream>
#include "SmartPointer/SmartPointer.h"
#include "BorrowingPointer/BorrowingPointer.h"

int main() {
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