#pragma once

#include "../../L5/SmartPointer/SmartPointer.h"

class Node;

template <typename T, typename E>
class Result
{
public:
    Result();
    explicit Result(const T& value);
    explicit Result(E* error);
    explicit Result(std::vector<E*>& errors);
    static Result success(const T& value);
    static Result fail(E* error);
    static Result fail(std::vector<E*>& errors);
    bool isSuccess();
    T getValue();
    std::vector<SmartPointer<E> >& getErrors();
private:
    SmartPointer<T> value;
    std::vector<SmartPointer<E> > errors;
    void swap(Result& other);
};

template <typename E>
class Result<void, E>
{
public:
    Result();
    explicit Result(E *error);
    explicit Result(std::vector<E*>& errors_given);
    static Result success();
    static Result fail(E* error);
    static Result fail(std::vector<E*>& errors);
    bool isSuccess();
    std::vector<SmartPointer<E> >& getErrors();
private:
    std::vector<SmartPointer<E> > errors;
};

template <typename E>
class Result<Node*, E>
{
public:
    Result();
    explicit Result(Node* value);
    explicit Result(E* error);
    explicit Result(std::vector<E*>& errors);
    static Result success(Node* value);
    static Result fail(E* error);
    static Result fail(std::vector<E*>& errors);
    bool isSuccess();
    Node* getValue();
    std::vector<SmartPointer<E> >& getErrors();
private:
    Node* value;
    std::vector<SmartPointer<E> > errors;
    void swap(Result& other);
};

template<typename T>
class Result<T, T>;