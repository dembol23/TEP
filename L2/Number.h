#ifndef L2_NUMBER_H
#define L2_NUMBER_H
#include <string>

class Number {
private:
    static const int BASE = 10;

    int size;
    int* array;
    bool isPositive;
    static int calculateSize(int number){
        if (number == 0) {
            return 1;
        }
        int size = 0;
        while (number != 0) {
            size++;
            number = number / BASE;
        }
        return size;
    };
    void fillArray(int number) const {
        if (!isPositive) {
            number = -number;
        }
        for (int i = 0; i < size; i++) {
            array[i] = number % BASE;
            number = number / BASE;
        }
    }
    void swap(Number &other) {
        std::swap(this->size, other.size);
        std::swap(this->array, other.array);
        std::swap(this->isPositive, other.isPositive);
    }
    Number addNumber(const Number &other) const;
    Number subtractNumber(const Number &other) const;
    Number multiplyNumber(const Number &other) const;
    Number divideNumber(const Number &other) const;

public:
    Number();
    Number(int number);
    Number(int *array, int size, bool isPositive);
    Number(const Number& other);
    ~Number();
    Number& operator=(int number);
    Number& operator=(const Number& number);
    Number operator+(const Number& other) const;
    Number operator-(const Number& other) const;
    Number operator*(const Number& other) const;
    Number operator/(const Number& other) const;
    Number &operator--();
    Number operator--(int);
    bool operator>=(const Number& other) const;
    std::string toString() const;
};

#endif