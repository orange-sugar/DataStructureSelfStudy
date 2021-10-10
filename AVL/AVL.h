#ifndef AVL_H
#define AVL_H

#include "../bst/bst.h"

template <typename T>
class AVL : public BST<T> {
public:
    BinNodePosi<T> insert(const T &);
    // bool remove(const T &);
};

template <typename T>
BinNodePosi<T> AVL<T>::insert(const T & e) {
    BinNodePosi<T> & x = this->search(e); if (x) return x;
    x = new BinNode<T>(e, this->_hot); this->_size++; BinNodePosi<T> xx = x;
    
    
}

#endif