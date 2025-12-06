#include <iostream>
#include "TwoDTable.h"

bool TwoDTableAllocation(int ***table, int rows, int cols) {
    if (cols < 1 || rows < 1) {
        std::cout << "Incorrect table size given" << std::endl;
        return false;
    }

    *table = new int*[rows];

    for (int i = 0; i < rows; i++) {
        (*table)[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            (*table)[i][j] = i * cols + j;
        }
    }

    return true;
}

bool TwoDTableDeallocation(int ***table, int rows) {
    if (rows < 1) {
        std::cout << "Incorrect table size given" << std::endl;
        return false;
    }

    if (table == NULL || *table == NULL) {
        std::cout << "Table not allocated" << std::endl;
        return false;
    }

    for (int i = 0; i < rows; i++) {
        delete[] (*table)[i];
    }

    delete[] *table;
    *table = NULL;

    return true;
}
