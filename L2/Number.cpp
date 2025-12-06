#include "Number.h"

#include <ostream>
#include <sstream>

Number::Number():size(1), array(new int[1]), isPositive(true) {
    array[0] = 0;
}

Number::Number(const int number)
    :size(calculateSize(number)), array(new int[size]), isPositive(number>=0) {
    fillArray(number);
}

Number::Number(int* array, const int size, const bool isPositive)
    :size(size), array(array), isPositive(isPositive) {}

Number::Number(const Number &other)
    :size(other.size), array(new int [other.size]), isPositive(other.isPositive) {
    for (int i = size - 1; i >= 0; i--) {
        array[i] = other.array[i];
    }
}

Number::~Number() {
    delete[] array;
}

Number& Number::operator=(const int number) {
    isPositive = number >= 0;
    const int newSize = calculateSize(number);
    if (newSize != size) {
        delete[] array;
        size = newSize;
        array = new int[size];
    }
    fillArray(number);
    return *this;
}

Number& Number::operator=(const Number &number) {
    Number temp(number);
    swap(temp);
    return *this;
}

std::string Number::toString() const {
    std::stringstream ss;
    if (!isPositive) {
        ss << "-";
    }
    for (int i = size - 1; i >= 0; i--) {
        ss << array[i];
    }
    return ss.str();
}

bool Number::operator>=(const Number& other) const {
    if (size < other.size) {return false;}
    if (size > other.size) {return true;}
    for (int i = size - 1; i >= 0; i--) {
        if (array[i] > other.array[i]) return true;
        if (array[i] < other.array[i]) return false;
    }
    return true;
}

Number Number::addNumber(const Number& other) const {
    int maxSize = std::max(size, other.size)+1;
    int* temp = new int[maxSize];
    int carry = 0;
    int sum = 0;
    for (int i = 0; i < maxSize; i++) {
        sum = carry;
        if (i < size) {
            sum += array[i];
        }
        if (i < other.size) {
            sum += other.array[i];
        }
        temp[i] = sum % BASE;
        carry = sum / BASE;
    }
    if (maxSize > 1 && temp[maxSize - 1] == 0) {
        maxSize--;
    }
    Number result(temp, maxSize, isPositive);
    return result;
}

Number Number::subtractNumber(const Number& other) const {
    int maxSize = size;
    int* temp = new int[maxSize];
    int borrow = 0;
    int difference = 0;
    int tempNum = 0;
    for (int i = 0; i < maxSize; i++) {
        tempNum = array[i];
        if (i < other.size) {
            tempNum -= other.array[i];
        }
        difference = tempNum - borrow;
        if (difference < 0) {
            difference += BASE;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        temp[i] = difference;
    }
    while (maxSize > 1 && temp[maxSize - 1] == 0) {
        maxSize--;
    }
    Number result(temp, maxSize, isPositive);
    return result;
}

Number Number::multiplyNumber(const Number& other) const {
    int maxSize = size + other.size;
    int* temp = new int[maxSize];
    for (int k = 0; k < maxSize; k++) {
        temp[k] = 0;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < other.size; j++) {
            const int product = array[i] * other.array[j];
            const int pos = i + j;
            const int sum = temp[pos] + product;
            temp[pos] = sum % BASE;
            temp[pos + 1] += sum / BASE;
        }
    }
    while (maxSize > 1 && temp[maxSize - 1] == 0) {
        maxSize--;
    }
    Number result(temp, maxSize, isPositive);
    return result;
}

Number Number::divideNumber(const Number& other) const {
    Number quotient(0);
    Number currentDividend(0);
    const Number base(BASE);

    Number positiveDivisor = other;
    positiveDivisor.isPositive = true;

    for (int i = size - 1; i >= 0; i--) {

        currentDividend = currentDividend.multiplyNumber(base);
        currentDividend = currentDividend.addNumber(Number(array[i]));
        int q = 0;
        bool q_found = false;
        for (int j = BASE - 1; j >= 1 && !q_found; j--) {
            Number product = positiveDivisor.multiplyNumber(Number(j));
            if (currentDividend >= product) {
                q = j;
                currentDividend = currentDividend.subtractNumber(product);
                q_found = true;
            }
        }
        quotient = quotient.multiplyNumber(base);
        quotient = quotient.addNumber(Number(q));
    }
    return quotient;
}

Number Number::operator+(const Number& other) const {
    Number result(0);
    if (isPositive == other.isPositive) { // A + B
        result = addNumber(other);
        result.isPositive = isPositive;
    }
    else if (*this >= other) { // A + (-B)
        result = subtractNumber(other);
        result.isPositive = isPositive;
    }
    else {
        result = other.subtractNumber(*this); // (-A) + B
        result.isPositive = other.isPositive;
    }
    if (result.size == 1 && result.array[0] == 0) { result.isPositive = true; }
    return result;
}

Number Number::operator-(const Number& other) const {
    Number tempOther = other;
    if (tempOther.size > 1 || tempOther.array[0] != 0) {
        tempOther.isPositive = !tempOther.isPositive;
    }
    return (*this) + tempOther;
}

Number Number::operator*(const Number& other) const {
    Number result = multiplyNumber(other);
    if (result.size == 1 && result.array[0] == 0) { result.isPositive = true; }
    else { result.isPositive = (isPositive == other.isPositive); }
    return result;
}

Number Number::operator/(const Number& other) const {
    if (other.size == 1 && other.array[0] == 0) {
        throw std::invalid_argument("Dzielenie przez zero!");
    }
    if (!(*this >= other)) {
        return Number(0);
    }
    Number result = divideNumber(other);
    result.isPositive = (isPositive == other.isPositive);
    return result;
}

Number& Number::operator--() {
    *this = *this - Number(1);
    return *this;
}

Number Number::operator--(int) {
    Number old(*this);
    --(*this);
    return old;
}


