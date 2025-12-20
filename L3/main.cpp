#include <iostream>

#include "Menu.h"
#include "Tree.h"

int main() {
    // Menu menu;
    // menu.run();
    Tree t1;
    t1.enter("+ + 1 2 * a f"); // Budujemy jakieś drzewo

    std::cout << "--- Test 1: Kopiowanie ---\n";
    Tree t2(t1);
    std::cout << t1.print() << std::endl;
    std::cout << "Liczba kopii: " << Tree::copy_counter << std::endl;
    std::cout << "Liczba przeniesień: " << Tree::move_counter << std::endl;
    Tree::resetCounters();

    std::cout << "--- Test 2: Przenoszenie ---\n";
    Tree t3 = std::move(t1);
    std::cout << t1.print() << std::endl;
    std::cout << "Liczba kopii: " << Tree::copy_counter << std::endl;
    std::cout << "Liczba przeniesień: " << Tree::move_counter << std::endl;
    Tree::resetCounters();

    std::cout << "--- Test 3: Dodawanie (zwracanie przez wartość) ---\n";
    Tree t4 = t2 + t3;
    std::cout << "Liczba kopii: " << Tree::copy_counter << std::endl;
    std::cout << "Liczba przeniesień: " << Tree::move_counter << std::endl;
    Tree::resetCounters();

    return 0;
}
