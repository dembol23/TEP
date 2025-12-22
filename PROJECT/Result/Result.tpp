#pragma once
#include <vector>

template<typename T, typename E>
Result<T, E>::Result():value(nullptr) {}

template<typename T, typename E>
Result<T, E>::Result(const T &value):value(new T(value)) {}

template<typename T, typename E>
Result<T, E>::Result(std::vector<SmartPointer<E>> &errors_given):value(nullptr) {
    for (int i = 0; i < errors_given.size(); ++i) {
        errors.push_back(errors_given[i]);
    }
}

template<typename T, typename E>
T Result<T, E>::getValue() {return value;}

template<typename T, typename E>
std::vector<SmartPointer<E>> &Result<T, E>::getErrors() {return errors;}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(E* error) {
    return Result(SmartPointer<E>(error));
}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(SmartPointer<E> error) {
    return Result(error);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(std::vector<SmartPointer<E>> &errors) {
    return Result(errors);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::success(const T &value) {
    return Result(value);
}

template<typename T, typename E>
bool Result<T, E>::isSuccess() {
    return errors.empty();
}

template<typename T, typename E>
std::string Result<T, E>::errorsToString() {
    std::string str;
    if (!errors.empty()) {
        for (int i = 0; i < errors.size(); i++) {
            str += '[' + std::to_string(i) + "]: " + errors[i]->getMessage() + "\n";
        }
    }
    else {
        str += "No Errors";
    }
    return str;
}


// Result z voidem

template<typename E>
Result<void, E>::Result() {}

template<typename E>
Result<void, E>::Result(SmartPointer<E> error) {
    errors.push_back(error);
}

template<typename E>
Result<void, E>::Result(std::vector<SmartPointer<E>> &errors_given) {
    for (int i = 0; i < errors_given.size(); ++i) {
        errors.push_back(errors_given[i]);
    }
}

template<typename E>
Result<void, E> Result<void, E>::fail(E* error) {
    return Result(SmartPointer<E>(error));
}

template<typename E>
Result<void, E> Result<void, E>::fail(SmartPointer<E> error) {
    return Result(error);
}

template<typename E>
Result<void, E> Result<void, E>::fail(std::vector<SmartPointer<E>> &errors) {
    return Result(errors);
}

template<typename E>
Result<void, E> Result<void, E>::success() {
    return Result();
}

template<typename E>
std::vector<SmartPointer<E>> &Result<void, E>::getErrors() {
    return errors;
}

template<typename E>
bool Result<void, E>::isSuccess() {
    return errors.empty();
}

template<typename E>
std::string Result<void, E>::errorsToString() {
    std::string str;
    if (!errors.empty()) {
        for (int i = 0; i < errors.size(); i++) {
            str += '[' + std::to_string(i) + "]: " + errors[i]->getMessage() + "\n";
        }
    }
    else {
        str += "No Errors";
    }
    return str;
}