#pragma once
#include <utility>

template<typename T>
SmartPointer<T>::SmartPointer(T *pointer) {
    this->pointer = pointer;
    if (this->pointer) {
        ref_counter = new ReferencesCounter();
        ref_counter->inc();
    }
    else {
        ref_counter = nullptr;
    }
}

template<typename T>
SmartPointer<T>::~SmartPointer() {
    release();
}

template<typename T>
SmartPointer<T> &SmartPointer<T>::operator=(const SmartPointer<T> &other){
    if (this == &other) return *this;

    release();

    pointer = other.pointer;
    ref_counter = other.ref_counter;
    if (this->ref_counter) {
        this->ref_counter->inc();
    }
    return *this;
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T> &other){
    this->pointer = other.pointer;
    ref_counter = other.ref_counter;
    if (this->ref_counter) {
        this->ref_counter->inc();
    }
}

template<typename T>
SmartPointer<T>::SmartPointer(SmartPointer<T> &&other) noexcept :pointer(other.pointer), ref_counter(other.ref_counter) {
    other.pointer = nullptr;
    other.ref_counter = nullptr;
}

template<typename T>
SmartPointer<T> &SmartPointer<T>::operator=(SmartPointer<T> &&other) noexcept {
    if (this == &other) return *this;

    release();

    pointer = std::exchange(other.pointer, nullptr);
    ref_counter = std::exchange(other.ref_counter, nullptr);

    return *this;
}

