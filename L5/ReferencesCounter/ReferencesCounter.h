#pragma once

class ReferencesCounter {
    public:
        ReferencesCounter():counter(1){};
        int add() { return ++counter; }
        int sub() { return --counter; }
        int get() const { return counter; }
    private:
        int counter;
};


