#ifndef SPLAY_H
#define SPLAY_H

#include "../bst/bst.h"
#include <cstdio>

template <typename T>
class Splay : public BST<T> {
protected:
    BinNodePosi<T> splay(BinNodePosi<T> v);
public:
    BinNodePosi<T> & search(const T & e);
    BinNodePosi<T> & insert(const T & e);
    bool remove(const T & e);
};

template <typename NodePosi> inline
void attachAsLC(NodePosi lc, NodePosi p) { p->lc = lc; if(lc) lc->parent = p; }

template <typename NodePosi> inline
void attachAsRC(NodePosi p, NodePosi rc) { p->rc = rc; if(rc) rc->parent = p; }

template <typename T>
BinNodePosi<T> Splay<T>::splay(BinNodePosi<T> v) {
    if (!v) return nullptr; BinNodePosi<T> p; BinNodePosi<T> g;
    while ((p= v->parent) && (g = p->parent)) {
        BinNodePosi<T> gg = g->parent;
        if (IsLChild(*v))
            if (IsLChild(*p)) {
                /*DSA*/printf ( "\tzIg-zIg :" ); print ( g ); print ( p ); print ( v ); printf ( "\n" );
                attachAsLC(p->rc, g); attachAsLC(v->rc , p);
                attachAsRC(p, g); attachAsRC(v, p);
            }
            else {
                /*DSA*/printf ( "\tzIg-zAg :" ); print ( g ); print ( p ); print ( v ); printf ( "\n" );
                attachAsLC(p, v->rc); attachAsRC(g, v->lc);
                attachAsLC(g, v); attachAsRC(v, p);
            }
        else if ( IsRChild ( *p ) ) { 
         /*DSA*/printf ( "\tzAg-zAg :" ); print ( g ); print ( p ); print ( v ); printf ( "\n" );
         attachAsRC ( g, p->lc ); attachAsRC ( p, v->lc );
         attachAsLC ( g, p ); attachAsLC ( p, v );
        } 
        else { 
         /*DSA*/printf ( "\tzAg-zIg :" ); print ( g ); print ( p ); print ( v ); printf ( "\n" );
         attachAsRC ( p, v->lc ); attachAsLC ( v->rc, g );
         attachAsRC ( v, g ); attachAsLC ( p, v );
        }
        if (!gg) v->parent = nullptr;
        else 
            (g == gg->lc) ? attachAsLC ( v, gg ) : attachAsRC ( gg, v );
        this->updateHeight ( g ); this->updateHeight ( p ); this->updateHeight ( v );    
    }
    if (p = v->parent) {
        /*DSA*/if ( IsLChild ( *v ) ) { printf ( "\tzIg :" ); print ( p ); print ( v ); printf ( "\n" ); }
        /*DSA*/else              { printf ( "\tzAg :" ); print ( p ); print ( v ); printf ( "\n" ); }
        if ( IsLChild ( *v ) ) { attachAsLC ( v->rc, p ); attachAsRC ( v, p ); }
        else                   { attachAsRC ( p, v->lc ); attachAsLC ( p, v ); }
        updateHeight ( p ); updateHeight ( v );
    }
    v->parent = nullptr; return v;
}

template <typename T>
BinNodePosi<T> & Splay<T>::search(const T & e) {
    BinNodePosi<T> p = this->searchIn(this->root, e, this->_hot = nullptr);
    this->_root = splay(p ? p : _hot);
    return _root;
}

template <typename T>
BinNodePosi<T> & Splay<T>::insert(const T & e) {
    if (!this->_root) { _this->_size++; reutrn new BinNode<T>(e); }
    if (e == search(e)->data) return this->_root;
    this->_size++; BinNodePosi<T> t = this->_root;
    if (this->_root->data < e) {
        t = new BinNode<T> (e, nullptr, t, t->rc);
        if (HasRChild(*t)) { t->rc->parent = this->_root; t->rc = nullptr; }
    }
    else {
        t->parent = _root = new BinNode<T> ( e, NULL, t->lc, t );
        if ( HasLChild ( *t ) ) { t->lc->parent = _root; t->lc = NULL; }
    }
    updateHeightAbove ( t );
    return _root; 
}

#endif