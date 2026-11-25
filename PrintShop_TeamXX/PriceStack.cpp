#include "PriceStack.h"

PriceStack::PriceStack() : topIndex(-1) {}

bool PriceStack::isFull() const {
    return topIndex == CAPACITY - 1;
}

bool PriceStack::isEmpty() const {
    return topIndex == -1;
}

int PriceStack::getCount() const {
    return topIndex + 1;
}

bool PriceStack::push(const PriceChangeRecord& rec) {
    if (isFull()) {
        return false;
    }
    topIndex++;
    elements[topIndex] = rec;
    return true;
}

bool PriceStack::pop(PriceChangeRecord& outRec) {
    if (isEmpty()) {
        return false;
    }
    outRec = elements[topIndex];
    topIndex--;
    return true;
}

bool PriceStack::peek(PriceChangeRecord& outRec) const {
    if (isEmpty()) {
        return false;
    }
    outRec = elements[topIndex];
    return true;
}
