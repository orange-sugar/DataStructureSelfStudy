#ifndef _BIN_NODE_MACRO_H
#define _BIN_NODE_MACRO_H

#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //����ӵ��һ������
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //ͬʱӵ����������
#define IsLeaf(x) ( ! HasChild(x) )

#define sibling( p ) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc ) /*�ֵ�*/
#define uncle( x ) ( sibling( (x)->parent ) ) /*����*/
#define FromParentTo( x ) /*���Ը��׵�����*/ \
   ( IsRoot(x) ? this->_root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )


// for AVL
#define HeightUpdated(x) \
         ( (x).height == 1 + max( stature( (x).lc ), stature( (x).rc ) ) )
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //����ƽ������
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //ƽ������
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVLƽ������

#endif