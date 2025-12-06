#include <iostream>
#include <ostream>
#include "TableAllocation.h"
#include "TwoDTable.h"
#include "CTable.h"


void tabMod(CTable table, int size) {
    table.setSize(size);
}
void tabMod(CTable *table, int size) {
    table->setSize(size);
}

int main() {
    std::cout << "=== Zadanie 1: Alokacja jednowymiarowej tablicy ===" << std::endl;
    TableAllocation(5);
    TableAllocation(0);

    std::cout << "\n=== Zadanie 2: Alokacja tablicy dwuwymiarowej ===" << std::endl;
    int **table2D = nullptr;
    if (TwoDTableAllocation(&table2D, 3, 4)) {
        std::cout << "Zawartość tablicy 2D:" << std::endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << table2D[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "\n=== Zadanie 3: Dealokacja tablicy dwuwymiarowej ===" << std::endl;
    if (TwoDTableDeallocation(&table2D, 4)) {
        std::cout << "Pamięć zwolniona poprawnie" << std::endl;
    } else {
        std::cout << "Błąd przy dealokacji" << std::endl;
    }

    std::cout << "\n=== Zadanie 4: Testowanie klasy CTable ===" << std::endl;

    std::cout << "\n--- Konstruktor domyślny ---" << std::endl;
    CTable t1;

    std::cout << "\n--- Konstruktor z parametrami ---" << std::endl;
    CTable t2("Test", 5);

    std::cout << "\n--- Konstruktor kopiujący ---" << std::endl;
    CTable t3(t2);

    std::cout << "\n--- Metoda setName ---" << std::endl;
    std::cout << t2.getName() << std::endl;
    t2.setName("Test2");
    std::cout << t2.getName() << std::endl;

    std::cout << "\n--- Metoda setSize ---" << std::endl;
    std::cout << t2.getSize() << std::endl;
    t2.setSize(10);
    std::cout << t2.getSize() << std::endl;

    std::cout << "\n--- Metoda clone ---" << std::endl;
    CTable* clone = t2.clone();
    delete clone;

    std::cout << "\n--- Funkcja modyfikująca przez wskaźnik ---" << std::endl;
    tabMod(&t2, 15);
    // dziala na oryginalnym obiekcie

    std::cout << "\n--- Funkcja modyfikująca przez wartość ---" << std::endl;
    tabMod(t2, 20); // nie zmieni oryginalnego obiektu
    // działa tylko na kopii i nie zmienia oryginalu i usuwa kopie

    std::cout << "\n--- Test alokacji tablicy obiektów ---" << std::endl;
    CTable* tabArray = new CTable[3]; // wywoła konstruktor 3 razy
    delete[] tabArray; // wywoła destruktory dla każdego obiektu

    std::cout << "\n--- Test alokacji statycznej obiektów ---" << std::endl;
    {
        CTable staticTab;
        CTable staticTab2("Static", 4);
    } // destruktory wywołają się automatycznie po wyjsciu ze scope

    std::cout << "\n--- Modyfikacja ---" << std::endl;

    CTable table("Mod", 1);
    CTable table2("Mod2", 1);
    int values[] = {1,2,3,4,5};
    int values2[] = {6,7,8,9,10};

    table.fillTable(values, 5);
    table.printTable();

    table2.fillTable(values2, 5);
    table2.printTable();

    table.insertHere(table2, 5);
    table.printTable();
    std::cout << "New size: " << table.getSize() << std::endl;

    return 0;
}

