#ifndef REDBLACK_H
#define REDBLACK_H

#include "../bst/bst.h"

template <typename T>
class RedBlack : public BST<T> {
protected:
    void solveDoubleRed(BinNodePosi<T> x);
    void solveDoubleBlack(BinNodePosi<T> x);
    int updateHeight(BinNodePosi<T> x);
public:
    BinNodePosi<T> insert(const T& e);
    bool remove(const T& e);
};

template <typename T>
int RedBlack<T>::updateHeight(BinNodePosi<T> x) {
    x->height = myMax(stature(x->lc), stature(x->rc));
    return IsBlack(x) ? x->height++ : x->height;
}

#endif