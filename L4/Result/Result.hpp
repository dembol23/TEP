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
    errors.push_back(SmartPointer<E>(error));
}

template<typename T, typename E>
Result<T, E>::Result(std::vector<E *> &errors_given):value(nullptr) {
    for (int i = 0; i < errors_given.size(); ++i) {
        errors.push_back(SmartPointer<E>(new E(*errors_given[i])));
    }
}

template<typename T, typename E>
T Result<T, E>::getValue() {return *value;}

template<typename T, typename E>
std::vector<SmartPointer<E> > &Result<T, E>::getErrors() {return errors;}

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
    errors.push_back(SmartPointer<E>(error));
}

template<typename E>
Result<void, E>::Result(std::vector<E *> &errors_given) {
    for (int i = 0; i < errors_given.size(); ++i) {
        errors.push_back(SmartPointer<E>(new E(*errors_given[i])));
    }
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
std::vector<SmartPointer<E> > &Result<void, E>::getErrors() {
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
    errors.push_back(SmartPointer<E>(error));
}

template<typename E>
Result<Node*, E>::Result(std::vector<E*>& errors_given) : value(nullptr) {
    for (size_t i = 0; i < errors_given.size(); ++i) {
        errors.push_back(SmartPointer<E>(new E(*errors_given[i])));
    }
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
bool Result<Node*, E>::isSuccess() {
    return errors.empty();
}

template<typename E>
Node* Result<Node*, E>::getValue() {
    return value;
}

template<typename E>
std::vector<SmartPointer<E> >& Result<Node*, E>::getErrors() {
    return errors;
}