#ifndef BIN_TREE_H
#define BIN_TREE_H

#include "BinNode.h"
#include "BinNode_macro.h"
#include "../_share/utils.h"
#include "../_share/release.h"


template <typename T> class BinTree
{
protected:
    int _size;
    BinNodePosi<T> _root;
    virtual int updateHeight(BinNodePosi<T> x);
    void updateHeightAbove(BinNodePosi<T> x); //更新x及其祖先节点高度

public:
    BinTree(): _size(0), _root(nullptr) { }

    ~BinTree() { if (0 < _size);  }

    int size() const { return _size; }
    bool empty() const { return !_root; }
    BinNodePosi<T> root() const { return _root; }

    BinNodePosi<T> insert(T const &);
    BinNodePosi<T> insert ( T const &, BinNodePosi<T> ); //插入左孩子
    BinNodePosi<T> insert ( BinNodePosi<T>, T const & ); //插入右孩子
    int remove(BinNodePosi<T> );

    //遍历
    template <typename VST>
    void travPre(VST& visit) { if (_root) _root->travPre(visit); }

    template <typename VST>
    void travIn(VST& visit) { if (_root) _root->travIn(visit); }

    // TODO TravPost


    template <typename VST>
    void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }
};

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi<T> x) {
    return x->height = 1 + myMax(stature(x->lc), stature(x->rc));
}

template <typename T> void BinTree<T>::updateHeightAbove ( BinNodePosi<T> x ){
     while ( x ) { updateHeight ( x ); x = x->parent; } 
}

template <typename T>
static int removeAt (BinNodePosi<T> x) {
    if (!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data); release(x); return n;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi<T> x) {
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);
    int n = removeAt(x); _size -= n; return n;
}

template <typename T>
BinNodePosi<T> BinTree<T>::insert(T const & e) {
    _size = 1; return _root = new BinNode<T> (e);
}

template <typename T>
BinNodePosi<T> BinTree<T>::insert ( T const & e, BinNodePosi<T> x) {
    _size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;
}

template <typename T>
BinNodePosi<T> BinTree<T>::insert ( BinNodePosi<T> x, T const & e) {
    _size++; x->insertAsRC(e); updateHeightAbove(x); return x->rc;
}


#endif