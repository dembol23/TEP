#include "Menu.h"
#include <iostream>
#include "../FileSaver/FileSaver.h"

template <typename T>
void printResultError(Result<T, Error>& result) {
    std::cout << "Operacja nieudana. Znaleziono bledy:" << std::endl;
    const std::vector<Error*>& errors = result.getErrors();
    for (int i = 0; i < errors.size(); ++i) {
        std::cout << " - " << errors[i]->getMessage() << std::endl;
    }
}

void printResultError(Result<void, Error>& result) {
    std::cout << "Operacja nieudana. Znaleziono bledy:" << std::endl;
    const std::vector<Error*>& errors = result.getErrors();
    for (size_t i = 0; i < errors.size(); ++i) {
        std::cout << " - " << errors[i]->getMessage() << std::endl;
    }
}

void Menu::handleEnter(const std::string& formula) {
    Result<void, Error> result = tree.enter(formula);
    if (result.isSuccess()) {
        std::cout << "Drzewo zbudowane pomyslnie." << std::endl;
    } else {
        printResultError(result);
    }
}

void Menu::handleVars() {
    std::cout << tree.vars() << std::endl;
}

void Menu::handlePrint() const {
    std::cout << tree.print() << std::endl;
}

void Menu::handleComp(const std::string &values) {
    Result<double, Error> r = tree.comp(values);
    if (r.isSuccess()) {
        std::cout << "Wynik: " << r.getValue() << std::endl;
    } else {
        printResultError(r);
    }
}

void Menu::handleJoin(const std::string &formula) {
    Result<void, Error> r = tree.join(formula);
    if (r.isSuccess()) {
        std::cout << "Drzewo dolaczone pomyslnie." << std::endl;
    } else {
        printResultError(r);
    }
}

void Menu::handleSave(const std::string& file_name) {
    if (file_name.empty()) {
        std::cout << "Musisz podac nazwe pliku." << std::endl;
        return;
    }
    Result<Node*, Error> r = tree.getTreeAsResult();
    FileSaver::save(r, file_name);

    std::cout << "Zapisano do pliku: " << file_name << std::endl;
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
                else if (command == "save") { // NOWE
                    handleSave(args);
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
