#include <iostream>
#include <stdint.h>

#include "stack_vector.h"
#include "../_share/utils.h"

#include "rpn.h"
// #include "../UNITPRINT/print.h"

using namespace std;


void convert(Stack<char> &S, signed long int n, int base) {
    char digit[] = "0123456789ABCDEF";
    while (n > 0) {
        S.push(digit[n % base]);
        n /= base;
    }
    while (!S.empty()) cout << S.pop();
}

void test_stack() {
    Stack<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    // s.traverse(print<int>);
    s.pop();s.pop();s.pop();
    Stack<char> s1;
    convert(s1, 10, 2);
}

void test_rpn() {
    char s[] = "(5+2)*5";
    char* rpn = ( char* ) malloc ( sizeof ( char ) * 1 );   rpn[0] = '\0';
    cout << s << " = " << evaluate(s, rpn) <<  endl;
    printf("%s", rpn);
}


int main() {
    // test_stack();
    test_rpn();
    return 0;
}