#pragma once
#include <vector>

#include "Result.tpp"

template<typename T, typename E>
void Result<T, E>::swap(Result &other) {
    std::swap(value, other.value);
    std::swap(errors, other.errors);
}

template<typename T, typename E>
Result<T, E>::Result():value(nullptr) {}

template<typename T, typename E>
Result<T, E>::Result(const T &value):value(new T(value)) {}

template<typename T, typename E>
Result<T, E>::Result(E *error):value(nullptr) {
    errors.push_back(error);
}

template<typename T, typename E>
Result<T, E>::Result(const Result &other):value(nullptr) {
    if (other.value != nullptr) {
        value = new T(*other.value);
    }
    for (int i = 0; i < other.errors.size(); ++i) {
        errors.push_back(new E(*other.errors[i]));
    }
}

template<typename T, typename E>
Result<T, E> &Result<T, E>::operator=(const Result &other) {
    if (this != &other) {
        Result temp(other);
        this->swap(temp);
    }
    return *this;
}

template<typename T, typename E>
Result<T, E>::Result(std::vector<E *> &errors_given):value(nullptr) {
    for (int i = 0; i < errors_given.size(); ++i) {
        errors.push_back(new E(*errors_given[i]));
    }
}

template<typename T, typename E>
Result<T, E>::~Result() {
    delete value;
    for (int i = 0; i < errors.size(); ++i) {
        delete errors[i];
    }
    errors.clear();
}

template<typename T, typename E>
T Result<T, E>::getValue() {return *value;}

template<typename T, typename E>
std::vector<E *> &Result<T, E>::getErrors() {return errors;}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(E *error) {
    return Result(error);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(std::vector<E *> &errors) {
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

// Result z voidem

template<typename E>
Result<void, E>::Result() {}

template<typename E>
Result<void, E>::Result(E *error) {
    errors.push_back(error);
}

template<typename E>
Result<void, E>::Result(const Result &other) {
    for (int i = 0; i < other.errors.size(); ++i) {
        errors.push_back(new E(*other.errors[i]));
    }
}

template<typename E>
Result<void, E>::Result(std::vector<E *> &errors_given) {
    for (int i = 0; i < errors_given.size(); ++i) {
        errors.push_back(new E(*errors_given[i]));
    }
}

template<typename E>
Result<void, E> &Result<void, E>::operator=(const Result &other) {
    if (this != &other) {
        Result temp(other);
        std::swap(this->errors, temp.errors);
    }
    return *this;
}

template<typename E>
Result<void, E>::~Result() {
    for (int i = 0; i < errors.size(); ++i) {
        delete errors[i];
    }
    errors.clear();
}

template<typename E>
Result<void, E> Result<void, E>::fail(E *error) {
    return Result(error);
}

template<typename E>
Result<void, E> Result<void, E>::fail(std::vector<E *> &errors) {
    return Result(errors);
}

template<typename E>
Result<void, E> Result<void, E>::success() {
    return Result();
}

template<typename E>
std::vector<E *> &Result<void, E>::getErrors() {
    return errors;
}

template<typename E>
bool Result<void, E>::isSuccess() {
    return errors.empty();
}

template<typename E>
void Result<Node*, E>::swap(Result &other) {
    std::swap(value, other.value);
    std::swap(errors, other.errors);
}

template<typename E>
Result<Node*, E>::Result() : value(nullptr) {}

template<typename E>
Result<Node*, E>::Result(Node* value) : value(value) {}

template<typename E>
Result<Node*, E>::Result(E* error) : value(nullptr) {
    errors.push_back(error);
}

template<typename E>
Result<Node*, E>::Result(std::vector<E*>& errors_given) : value(nullptr) {
    for (size_t i = 0; i < errors_given.size(); ++i) {
        errors.push_back(new E(*errors_given[i]));
    }
}

template<typename E>
Result<Node*, E>::Result(const Result& other) : value(other.value) {
    for (size_t i = 0; i < other.errors.size(); ++i) {
        errors.push_back(new E(*other.errors[i]));
    }
}

template<typename E>
Result<Node*, E>::~Result() {
    for (size_t i = 0; i < errors.size(); ++i) {
        delete errors[i];
    }
    errors.clear();
}

template<typename E>
Result<Node*, E> Result<Node*, E>::success(Node* value) {
    return Result(value);
}

template<typename E>
Result<Node*, E> Result<Node*, E>::fail(E* error) {
    return Result(error);
}

template<typename E>
Result<Node*, E> Result<Node*, E>::fail(std::vector<E*>& errors) {
    return Result(errors);
}

template<typename E>
Result<Node*, E>& Result<Node*, E>::operator=(const Result& other) {
    if (this != &other) {
        Result temp(other);
        this->swap(temp);
    }
    return *this;
}

template<typename E>
bool Result<Node*, E>::isSuccess() {
    return errors.empty();
}

template<typename E>
Node* Result<Node*, E>::getValue() {
    return value;
}

template<typename E>
std::vector<E*>& Result<Node*, E>::getErrors() {
    return errors;
}