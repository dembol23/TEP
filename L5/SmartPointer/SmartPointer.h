#pragma once
#include "../ReferencesCounter/ReferencesCounter.h"
#include "../BorrowingPointer/BorrowingPointer.h"

template <typename T>
class SmartPointer {
public:
    explicit SmartPointer(T *pointer);
    ~SmartPointer();
    SmartPointer(const SmartPointer<T> &other);
    SmartPointer(SmartPointer<T> &&other) noexcept;
    SmartPointer<T> &operator=( SmartPointer<T> &&other) noexcept;
    SmartPointer<T> &operator=(const SmartPointer<T> &other);

    T& operator*() const { return *pointer; }
    T* operator->() const { return pointer; }
    T* get() const { return pointer; }
    int getRefCounter() const { return ref_counter ? ref_counter->get() : 0; }
    bool isNull() const { return pointer == nullptr; }

    BorrowingPointer<T> borrow();

private:
    T* pointer;
    ReferencesCounter<T> * ref_counter;
    void release() {
        if (ref_counter && ref_counter->dec() == 0) {
            delete pointer;
            delete ref_counter;
        }
        pointer = nullptr;
        ref_counter = nullptr;
    }
};

#include "SmartPointer.tpp"