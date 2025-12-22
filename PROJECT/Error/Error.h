#pragma once
#include <string>


class Error {
public:
    Error();
    explicit Error(const std::string& message);
    Error(const Error& other);
    Error& operator=(const Error& other);
    ~Error();
    std::string getMessage();
private:
    std::string message;
};