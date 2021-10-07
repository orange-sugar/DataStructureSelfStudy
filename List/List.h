#ifndef LIST_H
#define LIST_H

#include "Listnode.h"
#include <iostream>

template <typename T>
class List {
public:
    // cstr and decstr
    List() { init(); }
    List(List<T> const& l) { copyNodes(l->first(), l->size()); }
    List(List<T> const& l, Rank r, int n) { ListNodePosi<T> tmp = l->first();
                                             while(0 < r--)  tmp = tmp->succ;
                                             copyNodes(tmp, n); }
    List(ListNodePosi<T> p, int n) { copyNodes(p, n); }
    ~List() { clear(); delete header; delete trailer; }

    ListNodePosi<T> first() const { return header->succ; }
    ListNodePosi<T> last() const { return trailer->pred; }

    ListNodePosi<T> find(T const& e) { return find(e, _size, trailer); }
    ListNodePosi<T> find(T const& e, int n, ListNodePosi<T> p);

    ListNodePosi<T> insertAsFirst(T const& e);
    ListNodePosi<T> insertAsLast(T const& e);
    ListNodePosi<T> insert(T const& e, ListNodePosi<T> p);
    ListNodePosi<T> insert(ListNodePosi<T> p, T const& e);

    T remove(ListNodePosi<T> p);

    int size() const { return _size; }
    bool empty() const { return 0 >= _size; }
    bool valid(ListNodePosi<T> p) { return p && (trailer != p) && (header != p); }

    int deduplicate(); //无序去重
    int uniquify(); //有序去重

    ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const;


// traverse
    void traverse(void(*) (T&));
    template <typename VST>
    void traverse(VST&);

protected:
    void init();
    void copyNodes(ListNodePosi<T> p, int n);
    int clear();
    

private:
    int _size; ListNodePosi<T> header; ListNodePosi<T> trailer;
};

// initialization on constrcution
template <typename T>
void List<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    trailer->pred = header;
    _size = 0;
}

template <typename T>
void List<T>::copyNodes(ListNodePosi<T> p, int n) {
    init();
    while(n--) { header->insertAsSucc(p->data); p = p->succ; }
}

template <typename T>
T List<T>::remove(ListNodePosi<T> p) {
    T e = p->data;
    p->pred->succ = p->succ; p->succ->pred = p->pred;
    delete p; _size--; // often missing "_size--"!!!!
    return e;
}

template <typename T>
int List<T>::clear() {
    int oldSize = _size;
    while(0 < _size) remove(header->succ);
    return oldSize;
}

// traverse
template <typename T> template <typename VST>
void List<T>::traverse(VST& visit) 
{ for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) visit(p->data); }

template <typename T> 
void List<T>::traverse(void(*visit)(T&)) 
{ for (ListNodePosi<T> p = header->succ; p != trailer; p = p->succ) visit(p->data); }

template <typename T>
ListNodePosi<T> List<T>::insertAsLast(T const& e) {
    _size++;
    return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi<T> List<T>::insertAsFirst(T const& e) {
    _size++;
    return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi<T> List<T>::insert(ListNodePosi<T> p, T const& e) {
    _size++;
    return p->insertAsSucc(e);
}

template <typename T>
ListNodePosi<T> List<T>::insert(T const& e, ListNodePosi<T> p) {
    _size++;
    return p->insertAsPred(e);
}

template <typename T>
ListNodePosi<T> List<T>::find(T const& e, int n, ListNodePosi<T> p) {
    while(0 < n--) 
        if (e == (p = p->pred)->data ) return p;
    return nullptr;
}

template <typename T>
int List<T>::deduplicate() {
    int oldSize = _size; ListNodePosi<T> p = first();
    for (Rank r = 0; p != trailer; p = p->succ) 
        if (ListNodePosi<T> q = find(p->data, r, p)) remove(q);
        else r++;
    return oldSize - _size;
}

template <typename T>
int List<T>::uniquify() {
    if (2 > _size) return 0;
    int oldSize = _size;
    ListNodePosi<T> p = first(); ListNodePosi<T> q;
    while (trailer != (q = p->succ))
        if (p->data != q->data) p = q;
        else remove(q);
    return oldSize - _size;
}

template <typename T>
ListNodePosi<T> List<T>::search(T const& e, int n, ListNodePosi<T> p) const {
    do {
        p = p->pred; n--;
    } while ((-1 < n) && (e < p->data));
    return p;
}

#endif