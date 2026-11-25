#ifndef PRICE_STACK_H
#define PRICE_STACK_H

#include "Models.h"

// Array Stack for Price Change History (Undo Stack)
class PriceStack {
public:
    static const int CAPACITY = 20;

private:
    PriceChangeRecord elements[CAPACITY];
    int topIndex;

public:
    PriceStack();

    bool isFull() const;
    bool isEmpty() const;
    int getCount() const;

    bool push(const PriceChangeRecord& rec);
    bool pop(PriceChangeRecord& outRec);
    bool peek(PriceChangeRecord& outRec) const;
};

#endif // PRICE_STACK_H
