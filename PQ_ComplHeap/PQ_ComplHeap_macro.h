#ifndef PQ_COMPLHEAP_MACRO_H
#define PQ_COMPLHEAP_MACRO_H

#define  Parent(i)         ( ( ( i ) - 1 ) >> 1 ) 
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) 
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) 
#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) 
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) 
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) 
#define  Bigger(PQ, i, j)  ( lt( PQ[i], PQ[j] ) ? j : i ) 
#define  ProperParent(PQ, n, i)  \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) 

#endif