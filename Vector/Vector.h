#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdlib.h>
#include <utility>
#include "../Fib/Fib.h"

using std::swap;

typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T>
Rank binSearch(T const *A, T const& e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        if (e < A[mi]) hi = mi;
        else if (A[mi] < e) lo = mi + 1;
        else if (e == A[mi]) return mi;
    }
    return -1;
}

template <typename T>
Rank fibSearch(T const *A, T const& e, Rank lo, Rank hi) {
    Fib fib(hi - lo);
    while (lo < hi) {
        Rank mi = fib.prev() - 1;
        if (e < A[mi]) hi = mi;
        else if (A[mi] < e) lo = mi + 1;
        else if (e == A[mi]) return mi;
    }
    return -1;
}

template <typename T>
class Vector {
    // friend std::ostream& operator<< (std::ostream &os, Vector<T> const &v) {
    //     for (int i = 0; i < v.size(); i++)
    //     os << v._elem[i] << " ";
    //     return os;
    // }  

protected:
    void copyFrom(T const *A, Rank lo, Rank hi);
    void expand();
    void shrink();
    void bubbleSort ( Rank lo, Rank hi ); 
    void mergeSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank mi, Rank hi);
    Rank _size;
    int _capacity;
    T *_elem;
public:
    // 默认、拷贝构造函�?
    // Vector(int c = DEFAULT_CAPACITY) { _elem = new T[ _capacity = c ]; _size = 0; }
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) 
    { _elem = new T[_capacity = s]; for (_size = 0; _size < s; _elem[_size++] = v); }
    Vector(T const *A, Rank n) { copyFrom(A, 0, n); }
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
    Vector(Vector<T> const &v) { copyFrom(v._elem, 0, v.size()); }
    Vector(Vector<T> const &v, Rank lo, Rank hi) { copyFrom(v._elem, lo, hi); }
    Vector<T>& operator =(const Vector<T> &v) { if(_elem) delete []_elem; copyFrom(v._elem, 0, v.size()); return *this; }

    // 析构函数
    ~Vector() { delete []_elem; }

    //只读访问接口
    Rank size() const { return _size; }                                     // 返回大小
    bool empty() const { return !_size; }                                   // 判空
    Rank find(T const& e) const { return find(e, 0, _size); }               // 无序向量查找
    Rank find(T const& e, Rank lo, Rank hi) const;                          
    Rank search(T const& e) const                                           // 有序向量查找
    { return (0 >= _size) ? -1 : serach(e, 0, _size); }
    Rank serach(T const& e, Rank lo, Rank hi) 
    { return (rand() % 2) ? 
            fibSearch(_elem, e, lo, hi) : binSearch(_elem, e, lo, hi); }
    
    // 读写
    void sort(Rank lo, Rank hi) { bubbleSort(lo, hi); }     // 排序
    Rank insert(Rank r, T const& e);                        // 插入接口
    Rank insert(T const& e) { return insert(_size, e); }

    T& operator[] (Rank r) { return _elem[r]; }
    const T& operator[] (Rank r) const { return _elem[r]; }
    
    T remove(Rank r);
    int remove(Rank lo, Rank hi);

    int deduplicate();
    int uniquify();

    // traverse
    void traverse(void (*)(T &e));

    template <typename VST>
    void traverse(VST& visit);
};

template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    for (_size = 0; lo < hi; _elem[_size++] = A[lo++]);
}

template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem; _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];

    delete [] oldElem;
}

template <typename T>
void Vector<T>::shrink() {
    if (_size < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity ) return;
    T* oldElem = _elem; _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
    delete [] oldElem;
}


template<typename T> //返回最后一个元素e的位置，失败则返�? lo - 1
Rank Vector<T>::find (T const& e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}

template <typename T>
void Vector<T>::bubbleSort ( Rank lo, Rank hi ) {
    for ( Rank last = --hi; lo < hi; hi = last)
        for (Rank i = last = lo; i < hi; i++)
            if (_elem[i] > _elem[i + 1])
                swap(_elem[last = i], _elem[i + 1]);
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi -lo < 2) return;
    Rank mi = (lo + hi) >> 1;
    mergeSort(lo, mi); 
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T* A = _elem + lo;
    int lb = mi - lo; T* B = new T[lb];
    // Rank ii = 0;
    for (Rank i = 0; i < lb; i++) B[i] = A[i];
    // for (ii = 0; ii < lb; B[ii] = A[ii++]) ;
    int lc = hi - mi; T* C = _elem + mi;
    Rank i = 0, j = 0, k = 0;
    while ( ( j < lb ) && ( k < lc ) )
        A[i++] = ( B[j] <= C[k] ) ? B[j++] : C[k++]; 
    while ( j < lb ) 
        A[i++] = B[j++]; 
    delete [] B;
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
    expand();
    for (int i = _size; i > r; i--) _elem[i] = _elem[i - 1];
    _elem[r]  = e; _size++;
    return r;
}

template <typename T>
void Vector<T>::traverse(void (*visit) (T &)) {
    for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit) 
{ for (int i = 0; i < _size; i++) visit(_elem[i]); }

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi) return 0;
    while (hi <_size) 
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template<typename T>
T Vector<T>::remove (Rank r) {
    T elem = _elem[r];
    remove(r, r + 1);
    return elem;
}

template <typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    for (int i = 0; i < _size; ++i) {
        Rank j = find(_elem[i], i++, _size);
        if (0 <= j) remove(j);
    }
    return oldSize - _size;
}

template <typename T>
int Vector<T>::uniquify() {
    // int oldSize = _size;
    Rank i = 0, j = 0;
    while (++j < _size)
    if (_elem[i] != _elem[j])
        _elem[++i] = _elem[j];
    remove(i + 1, _size);
    //return oldSize - _size;
    return j - i;
}
#endif