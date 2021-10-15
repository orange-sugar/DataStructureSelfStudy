#include "BTree.h"
#include "../_share/UniPrint/print.h"
#include <vector>

using namespace std;

void test_BTree() {
    
    BTree<int> bt;
    vector<int> elems{7, 3, 23, 2, 5, 19};//, 29, 17, 13};
    for (auto e : elems) {
        bt.insert(e);
    }
    print(bt);

}

int main() {
    test_BTree();
    return 0;
}