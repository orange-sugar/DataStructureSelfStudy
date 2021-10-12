#include "AVL.h"
#include <vector>
#include "../_share/UniPrint/print.h"

using namespace std;

void test_AVL() {
    // vector<int> elems{7, 3, 2, 23, 19};//, 23, 19, 29, 17, 13
    vector<int> elems{7, 3, 23, 2, 5, 19, 29, 17, 13};
    AVL<int> avl;
    for (auto e : elems) {
        avl.insert(e);
    }
    
    print(avl);
    avl.remove(7);
    print(avl);
}

int main() {
    test_AVL();
    return 0;
}