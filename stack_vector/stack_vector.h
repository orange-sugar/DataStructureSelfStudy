#ifndef STACK_VECTOR_H
#define STACK_VECTOR_H

#include "../Vector/Vector.h"

template <typename T> class Stack: public Vector<T> {
public: 
    void push (T const& e) { this->insert(e); }
    T pop() { return this->remove(this->size() - 1); }
    T& top() { return (*this)[this->size() - 1]; }
};

#endif