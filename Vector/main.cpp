#include "Vector.h"
#include <iostream>
#include <string>
//#include "../_share/utils.h"
#include "../_share/UniPrint/print.h"
using namespace std;


void test_Vector() {
    //Print<int> Print;
    int a[9] = {0, 0, 2, 3, 1, 6, 5, 3, 7};
    Vector<int> vec(a, 9);
    print(vec);
    Vector<int> b, c;
    // b = c = vec;
    // b.traverse(Print);
    // cout << endl;
    // b.sort(0, b.size());
    // b.traverse(Print);
    // cout << endl;
    
    // b.remove(b.find(5));
    // b.traverse(Print);
    // cout << endl;

    // b.uniquify();
    // b.traverse(Print);
    cout << endl;

    cout << b.search(2);
}

void test_othertype() {
    // Print<string> Print;
    // Vector<string> s;
    // s.insert(string("aa"));
    // s.traverse(Print);
   // vector<string> s;
}

int main() {
    test_Vector();
    // test_othertype();
    
    return 0;
}