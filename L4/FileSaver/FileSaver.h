#pragma once
#include <fstream>
#include <string>

#include "../Error/Error.h"
#include "../Result/Result.hpp"
#include "../Tree/Tree.h"


class FileSaver {
    public:
    template <typename T>
    static void save(Result<T, Error>& result, const std::string& filename) {
        std::ofstream file(filename.c_str(), std::ios::app);
        if (!file.is_open()) return;

        if (!result.isSuccess()) {
            file << "Bledy:\n";
            std::vector<Error*>& errors = result.getErrors();
            for (size_t i = 0; i < errors.size(); ++i) {
                file << errors[i]->getMessage() << "\n";
            }
            file << "-----------------\n";
        }
        file.close();
    }

    static void save(Result<void, Error>& result, const std::string& filename) {
        std::ofstream file(filename.c_str(), std::ios::app);
        if (!file.is_open()) return;
        if (!result.isSuccess()) {
            file << "Bledy:\n";
            std::vector<Error*>& errors = result.getErrors();
            for (size_t i = 0; i < errors.size(); ++i) {
                file << errors[i]->getMessage() << "\n";
            }
            file << "-----------------\n";
        }
        file.close();
    }

    static void save(Result<Node*, Error>& result, const std::string& filename) {
        std::ofstream file(filename.c_str(), std::ios::app);
        if (!file.is_open()) return;

        if (!result.isSuccess()) {
            file << "Bledy (podczas budowy drzewa):\n";
            std::vector<Error*>& errors = result.getErrors();
            for (size_t i = 0; i < errors.size(); ++i) {
                file << errors[i]->getMessage() << "\n";
            }
        } else {
            file << "Wynik (Drzewo prefix): ";
            file << result.getValue()->print();
        }
        file << "\n-----------------\n";
        file.close();
    }
};