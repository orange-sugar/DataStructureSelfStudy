#ifndef BST_H
#define BST_H

#include "../BinTree/BinTree.h"
using std::swap;

template <typename T> class BST: public BinTree<T> {
protected:
    BinNodePosi<T> _hot;
    BinNodePosi<T> connect34 ( 
      BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>,
      BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T> );
    BinNodePosi<T> rotateAt ( BinNodePosi<T> v ); 

public:
    virtual BinNodePosi<T>& search(T const&);
    virtual BinNodePosi<T> insert(const T &);
    virtual bool remove(const T&);
};


template <typename T>
BinNodePosi<T>& BST<T>::search(T const & e) {
    return searchIn(this->_root, e, _hot = nullptr);
}

template <typename T>
static BinNodePosi<T>& searchIn(BinNodePosi<T>& v, T const & e, BinNodePosi<T>& hot) {
    if (!v || e == v->data) return v;
    hot = v;
    return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);
}

template <typename T>
BinNodePosi<T> BST<T>::insert(const T & e) {
    BinNodePosi<T> &v = search(e); if (v) return v;
    v = new BinNode<T> (e, _hot);
    this->_size++;
    this->updateHeightAbove(v);
    return v;
}

template <typename T>
bool BST<T>::remove(const T& e) {
    BinNodePosi<T> & x = search(e);
    if (!x) return false;
    removeAt(x, _hot);
    this->_size--; this->updateHeightAbove(_hot);
    return true;
}

template <typename T>
static BinNodePosi<T> removeAt(BinNodePosi<T> &x, BinNodePosi<T> & hot) {
    BinNodePosi<T> w = x;
    BinNodePosi<T> succ = nullptr;
    if      (!HasLChild(*x)) succ = x = x->rc;
    else if (!HasRChild(*x)) succ = x = x->lc;
    else {
        w = w->succ(); swap(x->data, w->data);
        BinNodePosi<T> u = w->parent;
        ( ( u == x ) ? u->rc : u->lc ) = succ = w->rc; 
    }
    hot = w->parent;
    if (succ) succ->parent = hot;
    release(w->data); release(w);
    return succ;
}

template <typename T>
BinNodePosi<T> BST<T>::connect34 ( 
      BinNodePosi<T> a, BinNodePosi<T> b, BinNodePosi<T> c,
      BinNodePosi<T> T0, BinNodePosi<T> T1, BinNodePosi<T> T2, BinNodePosi<T> T3) {
    a->lc = T0; if ( T0 ) T0->parent = a;
    a->rc = T1; if ( T1 ) T1->parent = a; this->updateHeight ( a );
    c->lc = T2; if ( T2 ) T2->parent = c;
    c->rc = T3; if ( T3 ) T3->parent = c; this->updateHeight ( c );
    b->lc = a; a->parent = b;
    b->rc = c; c->parent = b; this->updateHeight ( b );
    return b;
}

template <typename T>
BinNodePosi<T> BST<T>::rotateAt ( BinNodePosi<T> v ) {
    if (!v) { printf("\a\nFail to rotate a null node\n"); exit(-1); }
    BinNodePosi<T> p = v->parent; BinNodePosi<T> g = p->parent;
    if (IsLChild(*p))
        if (IsLChild(*v)) { // zig-zig
            p->parent = g->parent;
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        }
        else { // zig-zag
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    else
        if (IsRChild(*v)) {
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        }
        else {
             v->parent = g->parent; //向上联接
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
} 


#endif