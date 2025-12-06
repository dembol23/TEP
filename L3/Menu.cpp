#include "Menu.h"

#include <iostream>

void Menu::handleEnter(const std::string& formula) {
    std::cout << tree.enter(formula) << std::endl;
}

void Menu::handleVars() {
    std::cout << tree.vars() << std::endl;
}

void Menu::handlePrint() const {
    std::cout << tree.print() << std::endl;
}

void Menu::handleComp(std::string &values) {
    std::cout << tree.comp(values) << std::endl;
}

void Menu::handleJoin(std::string &formula) {
    std::cout << "Drzewo dołączone. " << tree.join(formula) << std::endl;
}


void Menu::run() {
    bool running = true;
    std::cout << "Uruchomiono program drzewa. Dostepne komendy: enter, vars, print, comp, join, exit" << std::endl;

    while (running) {
        std::string line;
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            running = false;
        }
        else {
            if (!line.empty()) {
                std::string command;
                std::string args;
                const size_t spacePos = line.find(' ');
                if (spacePos != std::string::npos) {
                    command = line.substr(0, spacePos);
                    args = line.substr(spacePos + 1);
                } else {
                    command = line;
                    args = "";
                }

                if (command == "enter") {
                    handleEnter(args);
                }
                else if (command == "vars") {
                    handleVars();
                }
                else if (command == "print") {
                    handlePrint();
                }
                else if (command == "comp") {
                    handleComp(args);
                }
                else if (command == "join") {
                    handleJoin(args);
                }
                else if (command == "exit") {
                    running = false;
                }
                else {
                    std::cout << "Nieznana komenda." << std::endl;
                }
            }
        }
    }
}
