#ifndef BIN_NODE_H
#define BIN_NODE_H

#include "../stack_vector/stack_vector.h"
#include "../queue_list/queue_list.h"
#include "BinNode_macro.h"

#define stature(p) ((p) ? (p)->height : -1)

template <typename T> class BinNode;
template <typename T> using BinNodePosi = BinNode<T>* ;

template <typename T>
struct BinNode
{

    BinNodePosi<T> parent, lc, rc;
    T data; int height;


    BinNode(): parent(nullptr), lc(nullptr), rc(nullptr), height(0) { }
    BinNode ( T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL, BinNodePosi<T> rc = NULL,
             int h = 0) :
      data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ) { }

    

    int size();

   
    BinNodePosi<T> insertAsLC (T const& );
    BinNodePosi<T> insertAsRC (T const& );

    BinNodePosi<T> succ(); 

    template<typename VST> void travLevel(VST &);
    template<typename VST> void travPre(VST & visit) { travPre_I2(this, visit); }
    template<typename VST> void travIn(VST & visit) { travIn_I1(this, visit); }
    template<typename VST> void travPost(VST &);
};

template <typename T>
BinNodePosi<T> BinNode<T>::insertAsLC (T const& e) { return lc = new BinNode(e, this); }

template <typename T>
BinNodePosi<T> BinNode<T>::insertAsRC (T const& e) { return rc = new BinNode(e, this); }

template <typename T>
int BinNode<T>::size() {
    int s = 1;
    if (lc) s += lc->size(); if (rc) s += rc->size();
    return s;
}

template <typename T, typename VST>
void travIn_R (BinNodePosi<T> x, VST& visit) {
    if (!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

template <typename T, typename VST>
void travPre_R (BinNodePosi<T> x, VST& visit) {
    if (!x) return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template <typename T, typename VST>
void travPost_R (BinNodePosi<T> x, VST& visit) {
    if (!x) return;
    travIn_R(x->lc, visit);
    travIn_R(x->rc, visit);
    visit(x->data);
}

template <typename T, typename VST>
void travPre_I1 (BinNodePosi<T> x, VST& visit) {
    Stack<BinNodePosi<T>> stk;
    if (x) stk.push(x);
    while (!stk.empty()) {
        x = stk.pop();
        visit(x->data);
        if (HasLChild(*x)) stk.push(x->rc);
        if (HasRChild(*x)) stk.push(x->lc); 
    }
    
}

template <typename T, typename VST>
static void visitAlongVine( BinNodePosi<T> x, VST& visit, Stack<BinNodePosi<T>> &S ) {
    while (x) {
        visit(x->data);
        S.push(x->rc); x = x->lc;
    }
}

template <typename T, typename VST>
void travPre_I2 (BinNodePosi<T> x, VST& visit) {
    Stack<BinNodePosi<T>> S;
    S.push(x);
    do {
        x = S.pop();
        visitAlongVine(x, visit, S); 
    } while (!S.empty());
}

template <typename T>
static void goAlongVine(BinNodePosi<T> x, Stack<BinNodePosi<T>> & S) {
    while (x) {
        S.push(x); x = x->lc;
    }
}

template <typename T, typename VST>
void travIn_I1 (BinNodePosi<T> x, VST & visit) {
    Stack<BinNodePosi<T>> S;
    while (true) {
        goAlongVine(x, S);
        if (S.empty()) break;
        visit(S.top()->data);
        x = S.pop();
        // x = S.pop(); visit ( x->data );
        x = x->rc;
    }
}

template <typename T> template <typename VST> 
void BinNode<T>::travLevel(VST & visit) {
    Queue<BinNodePosi<T>> Q;
    // BinNodePosi<T> p = this;
    // visit(p->data);
    // Q.enqueue(p->lc); Q.enqueue(p->rc);
    // while(!Q.empty()) {
    //     if (p = Q.dequeue()) {visit(p->data); Q.enqueue(p->lc); Q.enqueue(p->rc); }
    // }
    Q.enqueue(this);
    while (!Q.empty()) {
        BinNodePosi<T> x = Q.dequeue(); visit(x->data);
        if (HasLChild(*x)) Q.enqueue(x->lc);
        if (HasRChild(*x)) Q.enqueue(x->rc);
    }
}

template <typename T>
BinNodePosi<T> BinNode<T>::succ() {
    BinNodePosi<T> s = this;
    if (rc) {
        s = rc;
        while (HasRChild(*s)) s = s->lc;
    }
    else {
        while (IsRChild(*s)) s = s->parent;
        s = s->parent;
    }
}

#endif