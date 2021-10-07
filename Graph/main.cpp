#include "GraphMatrix.h"
#include "../_share/UniPrint/print.h"

void importGraph ( GraphMatrix<char, int> & g ) {
   int n; scanf ( "%d\n", &n ); /*DSA*/printf ( "%d vertices\n", n );
   for ( int i = 0; i < n; i++ ) { //插入v个顶点
      char vertex; scanf ( "%c", &vertex );  /*DSA*/printf ( "Inserting vertex" ); print ( vertex ); printf ( " ..." );
      g.insert ( vertex );                  /*DSA*/printf ( "done\n" ); print ( g );
   }
   for ( int i = 0; i < n; i++ )
      for ( int j = 0; j < n; j++ ) { //插入边
         int edge; scanf ( "%d", &edge );
         if ( 0 > edge ) continue;             /*DSA*/printf ( "Inserting edge (%d, %d) = ", i, j ); print ( edge ); printf ( " ..." );
         g.insert ( edge, edge, i, j );        /*DSA*/printf ( "done\n" );
      }
}
void test_GraphMatrix() {
    GraphMatrix<char, int> g;
    importGraph(g);
    print(g);
}

int main(int argc, char* argv[]) {
    test_GraphMatrix();
    return 0;
}