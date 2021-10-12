#ifndef PRINT_H
#define PRINT_H

#include <cstdio>
#include "../../BinTree/BinTree.h"
#include "../../bitMap/Bitmap.h"
#include "../../Graph/GraphMatrix.h"
#include "../../Graph/Graph.h"
#include "../utils.h"
#include "../../bst/bst.h"
#include "../../AVL/AVL.h"

#define ROOT 0
#define L_CHILD 1
#define R_CHILD -1*L_CHILD


template <typename T> 
static void printBinTree ( BinNodePosi<T> bt, int depth, int type, Bitmap* bType );

// template <typename T> static void print ( const T& x ) {  UniPrint::p ( x );  } //for Stack
template <typename T> static int print ( T& x );
template <typename T> static void print ( T* x );

class UniPrint {
public:
    static void p (int e)   { printf(" %04d", e);  }
    static void p (float e) { printf(" %4.3f", e); }
    static void p (double e){ printf(" %4.3f", e); }
    static void p (char e)  { printf(" %c", ( 31 < e ) && ( e < 128 ) ? e : '$' ); }

    static void p ( VStatus e ){
       switch ( e ) {
       case UNDISCOVERED:   printf ( "U" ); break;
       case DISCOVERED:     printf ( "D" ); break;
       case VISITED:        printf ( "V" ); break;
       default:             printf ( "X" ); break;
   }
    }
    static void p ( EType e ) {
      switch ( e ) {
      case UNDETERMINED:   printf ( "U" ); break;
      case TREE:           printf ( "T" ); break;
      case CROSS:          printf ( "C" ); break;
      case BACKWARD:       printf ( "B" ); break;
      case FORWARD:        printf ( "F" ); break;
      default:             printf ( "X" ); break;
   }
    } 

    template <typename T> static void p ( BinNode<T>& ); 
    template <typename T> static void p ( BinTree<T>& ); 
    template <typename T> static void p ( BST<T>& ); //BST
    template <typename T> static void p ( AVL<T>& ); //AVL
    template <typename Tv, typename Te> static void p ( GraphMatrix<Tv, Te>& ); //Graph

};

template <typename T> static int print ( T& x ) {  UniPrint::p ( x ); return 0; }
template <typename T> static void print ( T* x ) {  x ? print ( *x ) : printf ( " <NULL>" );  }
template <typename T> static void print ( const T& x ) {  UniPrint::p ( x );  } //for Stack

template <typename T> void UniPrint::p (BinNode<T>& node ) {
    p(node.data);
    printf (
      ( node.lc && &node != node.lc->parent ) ||
      ( node.rc && &node != node.rc->parent ) ?
      "@" : " "
   );
}

template <typename T> 
void UniPrint::p ( BinTree<T> & bt ) { 
   printf ( "%s[%X]*%d:\n", typeid ( bt ).name(), &bt, bt.size() ); 
   Bitmap* branchType = new Bitmap; 
   printBinTree<T> ( bt.root(), -1, ROOT, branchType ); 
   release ( branchType ); printf ( "\n" );
}

template <typename T> //元素类型
static void printBinTree ( BinNodePosi<T> bt, int depth, int type, Bitmap* bType ) {
   if ( !bt ) return;
   if ( -1 < depth ) //设置当前层的拐向标志
      R_CHILD == type ? bType->set ( depth ) : bType->clear ( depth );
   printBinTree ( bt->rc, depth + 1, R_CHILD, bType ); //右子树（在上）
   print ( bt ); printf ( " *" );
   for ( int i = -1; i < depth; i++ ) //根据相邻各层
      if ( ( 0 > i ) || bType->test ( i ) == bType->test ( i + 1 ) ) //的拐向是否一致，即可确定
         printf ( "      " ); //是否应该
      else  printf ( "│    " ); //打印横线
   switch ( type ) {
      case  R_CHILD  :  printf ( "┌─" );  break;
      case  L_CHILD  :  printf ( "└─" );  break;
      default        :  printf ( "──" );  break; //root
   }
   print ( bt );
   printf ( "\n" );
   printBinTree ( bt->lc, depth + 1, L_CHILD, bType ); //左子树（在下）
}

template <typename Tv, typename Te> 
void UniPrint::p ( GraphMatrix<Tv, Te>& s ) { 
   int inD = 0; for ( int i = 0; i < s.n; i++ ) inD += s.inDegree ( i );
   int outD = 0; for ( int i = 0; i < s.n; i++ ) outD += s.outDegree ( i );
   printf ( "%s[%p]*(%d, %d):\n", typeid ( s ).name(), &s, s.n, s.e ); 

   print ( s.n ); printf ( " " ); print ( inD ); printf ( "|" );
   for ( int i = 0; i < s.n; i++ ) { print ( s.vertex ( i ) ); printf ( "[" ); print ( s.status ( i ) ); printf ( "] " ); }
   printf ( "\n" );

   print ( outD ); printf ( " " ); print ( s.e ); printf ( "|" );
   for ( int i = 0; i < s.n; i++ ) { print ( s.inDegree ( i ) ); printf ( " " ); }
   printf ( "| dTime fTime Parent Weight\n" );

   printf ( "-----------+" ); for ( int i = 0; i < s.n; i++ ) printf ( "------" );
   printf ( "+----------------------------\n" );

   for ( int i = 0; i < s.n; i++ ) {
      print ( s.vertex ( i ) ); printf ( "[" ); print ( s.status ( i ) ); printf ( "] " ); print ( s.outDegree ( i ) ); printf ( "|" );
      for ( int j = 0; j < s.n; j++ )
         if ( s.exists ( i, j ) ) { print ( s.edge ( i, j ) ); print ( s.type ( i, j ) ); }
         else printf ( "     ." );
      printf ( "| " ); print ( s.dTime ( i ) ); printf ( " " ); print ( s.fTime ( i ) );
      printf ( "     " ); if ( 0 > s.parent ( i ) ) print ( "^" ); else print ( s.vertex ( s.parent ( i ) ) );
      printf ( "  " ); if ( INT_MAX > s.priority ( i ) ) print ( s.priority ( i ) ); else print ( " INF" );
      printf ( "\n" );
   }
   printf ( "\n" );
}

template <typename T> //元素类型
void UniPrint::p ( BST<T> & bt ) { //引用
   printf ( "%s[%p]*%d:\n", typeid ( bt ).name(), &bt, bt.size() ); //基本信息
   Bitmap* branchType = new Bitmap; //记录当前节点祖先的方向
   printBinTree ( bt.root(), -1, ROOT, branchType ); //树状结构
   release ( branchType ); printf ( "\n" );
}

template <typename T> //元素类型
void UniPrint::p ( AVL<T> & avl ) { //引用
   printf ( "%s[%p]*%d:\n", typeid ( avl ).name(), &avl, avl.size() ); //基本信息
   Bitmap* branchType = new Bitmap; //记录当前节点祖先的方向
   printBinTree ( avl.root(), -1, ROOT, branchType ); //树状结构
   release ( branchType ); printf ( "\n" );
}



#endif