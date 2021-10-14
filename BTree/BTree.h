#ifndef BTREE_H
#define BTREE_H

#include "BTNode.h"
#include "../_share/release.h"

template <typename T> class BTree {
protected:
    int _size;
    int _order; //阶次
    BTNodePosi<T> _root;
    BTNodePosi<T> _hot;
    void solveOverflow(BTNodePosi<T>);
    void solveUnderflow(BTNodePosi<T>);

public:
    BTree(int order = 3) : _order(order), _size(0)
    { _root = new BTNode<T> (); }
    ~BTree() { if (_root) release(_root); }
    int order() const { return _order; }
    int size() const { return _size; }
    BTNodePosi<T> & root() { return _root; }
    bool empty() const { return !_root; }

    BTNodePosi<T> search(const T& e);
    bool insert(const T& e);
    bool remove(const T& e);
};

template <typename T>
BTNodePosi<T> BTree<T>::search(const T& e) {
    BTNodePosi<T> v = _root; _hot = nullptr;
    while (v) {
        Rank x = v->key.search(e);
        if ((0 <= x) && (e == v->key[r])) return v;
        v = v->child[x + 1]; _hot = v;
    }  
    return nullptr;
}

#endif