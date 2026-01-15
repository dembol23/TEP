#pragma once
#include <vector>

template <typename T>
class BorrowingPointer;

template <typename T>
class ReferencesCounter {
public:
    ReferencesCounter() : counter(0) {}
    ~ReferencesCounter();
    void addBorrowingPointer(BorrowingPointer<T>* ptr);
    void removeBorrowingPointer(BorrowingPointer<T>* ptr);

    int inc() { return ++counter; }
    int dec() { return --counter; }
    int get() const { return counter; }

private:
    int counter;
    std::vector<BorrowingPointer<T>*> borrowingPointers;
};