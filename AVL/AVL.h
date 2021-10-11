#ifndef AVL_H
#define AVL_H

#include "../bst/bst.h"
#include "AVL_macro.h"

template <typename T>
class AVL : public BST<T> {
public:
    BinNodePosi<T> insert(const T &);
    // bool remove(const T &);
};

template <typename T>
BinNodePosi<T> AVL<T>::insert(const T & e) {
    BinNodePosi<T> & x = this->search(e); if (x) return x;
    BinNodePosi<T> xx = x = new BinNode<T>(e, this->_hot); this->_size++;
    for (BinNodePosi<T> g = this->_hot; g; g = g->parent)
        if (!AvlBalanced(*g)) {
            auto &s = FromParentTo(*g);
            //auto ss = this->rotateAt(tallerChild(tallerChild(g)));
            //FromParentTo(*g) 
            s = this->rotateAt(tallerChild(tallerChild(g)));
            break;
        }
        else 
            this->updateHeight(g);
    return xx;   
}

#endif