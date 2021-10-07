#include <iostream>
#include "BinTree.h"
#include "../_share/utils.h"
#include "../_share/double_Elem.h"
#include "../_share/UniPrint/print.h"

using namespace std;

void test_BinTree() {
    Double<int> Double;
    Print<int> Print;
    BinTree<int> bt;
    bt.insert(2); bt.insert(1, bt.root()); bt.insert(bt.root(), 3);
    bt.insert(bt.root()->rc, 4); bt.insert(4, bt.root()->rc);
    bt.insert(6, bt.root()->lc);
    // bt.travPre(Print);
    // bt.travPre(Double);
    bt.travPre(Print); printf("\n");
    bt.travIn(Print);  printf("\n");
    bt.travLevel(Print);  printf("\n");
    // bt.travPre(Print);

    print (bt);
}

int main() {
    test_BinTree();    
    return 0;
}