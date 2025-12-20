#pragma once

template<typename T>
SmartPointer<T>::SmartPointer(T *pointer)
:pointer(pointer),ref_counter(new ReferencesCounter()) {}

template<typename T>
SmartPointer<T>::~SmartPointer() {
    if (ref_counter->sub() == 0) {
        delete pointer;
        delete ref_counter;
    }
}

template<typename T>
SmartPointer<T> &SmartPointer<T>::operator=(const SmartPointer<T> &other) {
    if (this == &other) return *this;
    if (ref_counter->sub() == 0) {
        delete pointer;
        delete ref_counter;
    }
    pointer = other.pointer;
    ref_counter = other.ref_counter;
    ref_counter->add();
    return *this;
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T> &other){
    this->pointer = other.pointer;
    other.ref_counter->add();
    ref_counter = other.ref_counter;
}

