#ifndef DOUBLE_ELEM_H
#define DOUBLE_ELEM_H

template <typename T> struct Double {
    virtual void operator() (T& e) {e *= 2;}
};

#endif