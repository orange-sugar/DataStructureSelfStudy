#include "bst.h"
#include "../_share/UniPrint/print.h"

void test_bst() {
    Print<int> Print;
    BST<int> bst;
    bst.insert(2); bst.insert(1); bst.insert(3);
    bst.remove(3);
    bst.travIn(Print);
    printf("\n");
    print(bst);
}

int main() {
    test_bst();
    return 0;
}