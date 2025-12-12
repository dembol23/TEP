#include <iostream>
#include <string>
#include <vector>

// Dołączamy nagłówki twojego projektu
#include "Result/Result.hpp"
#include "Error/Error.h"
#include "Tree/Node.h"

// Funkcja pomocnicza do wypisywania błędów
void printErrors(std::vector<Error*>& errors) {
    for (size_t i = 0; i < errors.size(); ++i) {
        std::cout << "  [!] Blad: " << errors[i]->getMessage() << std::endl;
    }
}

int main() {
    std::cout << "=== TESTY KLASY RESULT ===" << std::endl;

    // ---------------------------------------------------------
    // TEST 1: Standardowy Result<int, Error> - SUKCES
    // ---------------------------------------------------------
    std::cout << "\n1. Test Result<int, Error> (Sukces):" << std::endl;
    Result<int, Error> resIntSuccess = Result<int, Error>::success(42);

    if (resIntSuccess.isSuccess()) {
        std::cout << "  OK. Wartosc: " << resIntSuccess.getValue() << std::endl;
    } else {
        std::cout << "  BLAD. Oczekiwano sukcesu." << std::endl;
    }

    // ---------------------------------------------------------
    // TEST 2: Standardowy Result<int, Error> - PORAŻKA
    // ---------------------------------------------------------
    std::cout << "\n2. Test Result<int, Error> (Porazka):" << std::endl;
    Result<int, Error> resIntFail = Result<int, Error>::fail(new Error("Nie udalo sie obliczyc"));

    if (!resIntFail.isSuccess()) {
        std::cout << "  OK. Operacja sie nie udala." << std::endl;
        printErrors(resIntFail.getErrors());
    } else {
        std::cout << "  BLAD. Oczekiwano bledu." << std::endl;
    }

    // ---------------------------------------------------------
    // TEST 3: Specjalizacja Result<void, Error>
    // ---------------------------------------------------------
    std::cout << "\n3. Test Result<void, Error>:" << std::endl;
    Result<void, Error> resVoid = Result<void, Error>::success();
    if (resVoid.isSuccess()) std::cout << "  OK (Void sukces)" << std::endl;

    Result<void, Error> resVoidFail = Result<void, Error>::fail(new Error("Void error"));
    if (!resVoidFail.isSuccess()) {
        std::cout << "  OK (Void porazka): ";
        printErrors(resVoidFail.getErrors());
    }

    // ---------------------------------------------------------
    // TEST 4: Specjalizacja Result<Node*, Error>
    // ---------------------------------------------------------
    std::cout << "\n4. Test Result<Node*, Error>:" << std::endl;
    Node* myNode = new Node("test_node", NODE_CONSTANT);
    Result<Node*, Error> resNode = Result<Node*, Error>::success(myNode);

    if (resNode.isSuccess()) {
        std::cout << "  OK. Mamy wezel o wartosci: " << resNode.getValue()->getValue() << std::endl;
    }
    delete myNode;

    // ---------------------------------------------------------
    // TEST 5: TEST BLOKADY TYPÓW (TO ZADANIE Z LISTY)
    // ---------------------------------------------------------
    std::cout << "\n5. Test blokady identycznych typow (Result<T, T>):" << std::endl;
    // Result<int, int> blockedResult;
    // Result<double, double>::success(5.0);
    // Result<Error*, Error*> weirdResult;

    return 0;
}