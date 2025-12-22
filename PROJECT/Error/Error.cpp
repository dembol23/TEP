#include "Error.h"

Error::Error():message("An error occurred") {}

Error::Error(const std::string &message):message(message) {}

Error::Error(const Error &other) : message(other.message) {}

Error &Error::operator=(const Error &other) {
    if (this != &other) {
        message = other.message;
    }
    return *this;
}

Error::~Error() = default;

std::string Error::getMessage() {
    return message;
}