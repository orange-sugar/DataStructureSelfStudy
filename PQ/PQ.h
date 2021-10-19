#ifndef PQ_H
#define PQ_H

template<typename T> struct PQ {
    virtual void insert(T) = 0;
    virtual T getMax() = 0;
    virtual T dekMax() = 0;
};

#endif