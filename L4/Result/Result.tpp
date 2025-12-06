#pragma once
template <typename T, typename E>
class Result
{
public:
    Result();
    explicit Result(const T& value);
    explicit Result(E* error);
    explicit Result(std::vector<E*>& errors);
    Result(const Result& other);
    ~Result();
    static Result success(const T& value);
    static Result fail(E* error);
    static Result fail(std::vector<E*>& errors);
    Result& operator=(const Result& other);
    bool isSuccess();
    T getValue();
    std::vector<E*>& getErrors();
private:
    T *value;
    std::vector<E*> errors;
    void swap(Result& other);
};

template <typename E>
class Result<void, E>
{
public:
    Result();
    explicit Result(E *error);
    explicit Result(std::vector<E*>& errors_given);
    Result(const Result& other);
    ~Result();
    static Result success();
    static Result fail(E* error);
    static Result fail(std::vector<E*>& errors);
    Result& operator=(const Result& other);
    bool isSuccess();
    std::vector<E*>& getErrors();
private:
    std::vector<E*> errors;
};