#ifndef AVL_MACRO_H
#define AVL_MACRO_H

#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*���*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*�Ҹ�*/ \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc /*�ȸߣ��븸��xͬ���ߣ�zIg-zIg��zAg-zAg������*/ \
   ) \
   ) \
)

#endif

