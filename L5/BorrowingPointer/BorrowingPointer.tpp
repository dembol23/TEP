#pragma once

template <typename T>
ReferencesCounter<T>::~ReferencesCounter() {
    for (auto ptr : borrowingPointers) {
        ptr->expire();
    }
}

template <typename T>
void ReferencesCounter<T>::addBorrowingPointer(BorrowingPointer<T>* ptr) {
    borrowingPointers.push_back(ptr);
}

template <typename T>
void ReferencesCounter<T>::removeBorrowingPointer(BorrowingPointer<T>* ptr) {
    for (auto it = borrowingPointers.begin(); it != borrowingPointers.end(); ++it) {
        if (*it == ptr) {
            borrowingPointers.erase(it);
            return;
        }
    }
}