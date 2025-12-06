#pragma once
#include "Tree.h"

class Menu {
public:
    void run();
private:
    Tree tree;
    void handleEnter(const std::string& formula);
    void handlePrint() const;
    void handleVars();
    void handleComp(const std::string& values);
    void handleJoin(const std::string& formula);
    void handleSave(const std::string& file_name);
};