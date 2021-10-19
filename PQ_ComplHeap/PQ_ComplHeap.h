#ifndef PQ_COMPLHEAP_H
#define PQ_COMPLHEAP_H

#include "../Vector/Vector.h"
#include "PQ_ComplHeap_macro.h"
#include "../_share/comparator.h"
#include "../PQ/PQ.h"
#include <utility>

using std::swap;

template<typename T> class PQ_ComplHeap : public PQ<T>, public Vector<T> {
protected: 
    Rank percolateDown(Rank n, Rank i);
    Rank percolateUp(Rank i);
    void heapify(Rank n);
public:
    PQ_ComplHeap() { }
    PQ_ComplHeap(T* A, Rank n) { this->copyFrom(A, 0, n); heapify(n); }
    void insert(T e) {
        Vector<T>::insert(e);
        percolateUp(this->_size - 1);
    }
    T getMax() { return this->_elem[0]; }
    T delMax();

};

template<typename T> 
Rank PQ_ComplHeap<T>::percolateUp(Rank i) {
    while (0 < i) {
        Rank j = Parent(i);
        if (lt(this->_elem[i], this->_elem[j])) break;
        swap(this->_elem[i], this->_elem[j]);
    }
    return i;
}

#endif