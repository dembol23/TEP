#pragma once

class ReferencesCounter {
    public:
        ReferencesCounter():counter(1){};
        int inc() { return ++counter; }
        int dec() { return --counter; }
        int get() const { return counter; }
    private:
        int counter;
};


