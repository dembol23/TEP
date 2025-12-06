#include <iostream>
#include "TableAllocation.h"

void TableAllocation(int size) {
    if (size < 1) {
        std::cout << "Incorrect table size given" << std::endl;
        return;
    }

    int *table = new int[size];

    for (int i = 0; i < size; i++) {
        table[i] = DEFAULT_FILL_VALUE;
    }
    for (int i = 0; i < size; i++) {
        std::cout << table[i] << std::endl;
    }
    delete[] table;
}

