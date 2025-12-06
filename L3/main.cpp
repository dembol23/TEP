#include <iostream>

#include "Menu.h"
#include "Tree.h"

int main() {
    Tree tree;
    // tree.enter("+ + a b + c d");
    // tree.enter("- * + a b + c d e");
    // tree.vars();
    // std::cout << tree.comp("1.1 2 3 4 0.33") << std::endl;
    // tree.enter("cos chuj");
    // tree.vars();
    // std::cout << tree.comp("3.141") << std::endl;
    // tree.enter("+ a b");
    // tree.vars();
    // tree.join("+ c d");
    // tree.vars();
    Menu menu;
    menu.run();
    return 0;
}
