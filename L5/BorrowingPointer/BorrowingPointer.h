#pragma once
#include "../ReferencesCounter/ReferencesCounter.h"

template <typename T>
class BorrowingPointer {
public:
    BorrowingPointer(T* pointer, ReferencesCounter<T>* rc) : pointer(pointer), ref_counter(rc) {
        if (ref_counter) ref_counter->addBorrowingPointer(this);
    }

    BorrowingPointer(const BorrowingPointer& other) : pointer(other.pointer), ref_counter(other.ref_counter) {}

    BorrowingPointer& operator=(const BorrowingPointer<T>& other) {
        if (this == &other) return *this;
        if (ref_counter) ref_counter->removeBorrowingPointer(this);

        pointer = other.pointer;
        ref_counter = other.ref_counter;
        if (ref_counter) ref_counter->addBorrowingPointer(this);
        return *this;
    }

    ~BorrowingPointer() {
        if (ref_counter) ref_counter->removeBorrowingPointer(this);
    }

    void expire() {
        pointer = nullptr;
        ref_counter = nullptr;
    }

    void setPointer(T* new_pointer) {
        pointer = new_pointer;
    }

    T& operator*() const { return *pointer; }
    T* operator->() const { return pointer; }
    T* get() const { return pointer; }
    bool isNull() const { return pointer == nullptr; }

private:
    T* pointer;
    ReferencesCounter<T>* ref_counter;
};

#include "BorrowingPointer.tpp"