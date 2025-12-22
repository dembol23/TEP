#pragma once

#include <vector>
#include "../../L5/SmartPointer/SmartPointer.h"

class Node;

template <typename T, typename E>
class Result
{
public:
    Result();
    explicit Result(const T& value);
    explicit Result(std::vector<SmartPointer<E>> &errors_given);
    static Result success(const T& value);
    static Result fail(E* error);
    static Result fail(SmartPointer<E> error);
    static Result fail(std::vector<SmartPointer<E>>& errors);
    bool isSuccess();
    T getValue();
    std::vector<SmartPointer<E>>& getErrors();
private:
    SmartPointer<T> value;
    std::vector<SmartPointer<E>> errors;
};

template <typename E>
class Result<void, E>
{
public:
    Result();
    explicit Result(SmartPointer<E> error);
    explicit Result(std::vector<SmartPointer<E>>& errors_given);
    static Result success();
    static Result fail(E* error);
    static Result fail(SmartPointer<E> error);
    static Result fail(std::vector<SmartPointer<E>>& errors);
    bool isSuccess();
    std::vector<SmartPointer<E>>& getErrors();
private:
    std::vector<SmartPointer<E>> errors;
};

#include "Result.tpp"