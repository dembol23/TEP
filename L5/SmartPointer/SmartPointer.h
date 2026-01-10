#pragma once
#include "../ReferencesCounter/ReferencesCounter.h"

template <typename T>
class SmartPointer {
    public:
        explicit SmartPointer(T *pointer);
        ~SmartPointer();
        SmartPointer(const SmartPointer<T> &other);
        SmartPointer<T> &operator=(const SmartPointer<T> &other);
        T& operator*() const { return *pointer; }
        T* operator->() const { return pointer; }
        int getRefCounter() const { return ref_counter->get(); }
        bool isNull() const { return pointer == nullptr; }
    private:
        T* pointer;
        ReferencesCounter* ref_counter;
};

#include "SmartPointer.tpp"


