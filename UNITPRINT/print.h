#include <cstdio>

class UniPrint;

template <typename T> static void print ( const T& x ) {  UniPrint::p ( x );  }

class UniPrint {
    template <typename T> static void p (T &s) {
        printf ( "%s[%d]*%d:\n", typeid ( s ).name(), (int) &s, s.size() ); //基本信息
        s.traverse ( print ); //通过print()遍历输出所有元素
        printf ( "\n" );
    }
};

