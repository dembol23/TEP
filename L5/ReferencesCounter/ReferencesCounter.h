#pragma once
#include <vector>

template <typename T>
class BorrowingPointer;

template <typename T>
class ReferencesCounter {
public:
    ReferencesCounter() : counter(0) {}
    ~ReferencesCounter() {
        clearBorrowingPointers();
    }

    void addBorrowingPointer(BorrowingPointer<T>* ptr) {
        borrowingPointers.push_back(ptr);
    }

    void removeBorrowingPointer(BorrowingPointer<T>* ptr) {
        for (size_t i = 0; i < borrowingPointers.size(); ++i) {
            if (borrowingPointers[i] == ptr) {
                if (i != borrowingPointers.size() - 1) {
                    std::swap(borrowingPointers[i], borrowingPointers.back());
                }
                borrowingPointers.pop_back();
                return;
            }
        }
    }

    int inc() { return ++counter; }
    int dec() { return --counter; }
    int get() const { return counter; }

    void clearBorrowingPointers() {
        for (auto ptr : borrowingPointers) {
            if (ptr) ptr->expire();
        }
        borrowingPointers.clear();
    }

private:
    int counter;
    std::vector<BorrowingPointer<T>*> borrowingPointers;
};