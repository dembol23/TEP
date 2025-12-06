
#include "CTable.h"

#include <iostream>

CTable::CTable() {
    table_name = DEFAULT_NAME;
    table_size = DEFAULT_SIZE;
    table = new int [table_size];
    std::cout << "Default constructor: " << table_name << std::endl;
}

CTable::CTable(const std::string& name, int size) {
    table_name = name;
    if (size < 1) {
        table_size = DEFAULT_SIZE;
    }
    else {
        table_size = size;
    }
    table = new int [table_size];
    std::cout << "Params constructor: " << table_name << std::endl;
}

CTable::CTable(CTable const &template_table) {
    table_name = template_table.table_name + "_copy";
    table_size = template_table.table_size;
    table = new int [table_size];
    for (int i = 0; i < table_size; i++) {
        table[i] = template_table.table[i];
    }
    std::cout << "Copied: " << table_name << std::endl;
}

CTable::~CTable() {
    delete[] table;
    std::cout << "Deleting: " << table_name << std::endl;
}

void CTable::setName(const std::string& name) {
    table_name = name;
}

std::string CTable::getName() const {
    return table_name;
}

bool CTable::setSize(int size) {
    if (size > 0) {
        table_size = size;
        delete[] table;
        table = new int [table_size];
        return true;
    }
    return false;
}

int CTable::getSize() const {
    return table_size;
}

CTable* CTable::clone() const {
    return new CTable(*this);
}

void CTable::fillTable(int *list, int size) {
    if (list == NULL || size < 1) return;
    setSize(size);
    for (int i = 0; i < table_size; i++) {
        table[i] = list[i];
    }
}

void CTable::printTable() {
    for (int i = 0; i < table_size; i++) {
        std::cout << table[i] << " ";
    }
    std::cout << std::endl;
}

void CTable::insertHere(CTable &table_given, int position) {
    if (position > getSize() || position < 0) {
        std::cout << "Position out of bounds: " << position << std::endl;
        return;
    }

    const int new_size = table_given.getSize() + table_size;
    int *new_table = new int[new_size];
    int new_table_index = 0;

    for (int i = 0; i < position; i++) {
        new_table[new_table_index++] = table[i];
    }

    for (int i = 0; i < table_given.getSize(); i++) {
        new_table[new_table_index++] = table_given.table[i];
    }

    for (int i = position; i < table_size; i++) {
        new_table[new_table_index++] = table[i];
    }

    delete[] table;
    table = new_table;
    table_size = new_size;
}