#ifndef L3_MENU_H
#define L3_MENU_H
#include "Tree.h"


class Menu {
    private:
    Tree tree;
    void handleEnter(const std::string& formula);
    void handlePrint() const;
    void handleVars();
    void handleComp(std::string& values);
    void handleJoin(std::string& formula);
public:
    void run();
};


#endif //L3_MENU_H