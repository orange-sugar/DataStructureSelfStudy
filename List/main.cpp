#include <iostream>
#include "list.h"

using namespace std;

template <typename T>
void print(T &data) {
    cout << data << "->";
}

void test_List() {
    List<int> l;
    l.insertAsLast(1);
    l.insertAsLast(1);
    l.insertAsLast(2);
    l.insertAsLast(2);
    l.insertAsLast(2);
    l.insertAsLast(3);
    l.traverse(print<int>);
    cout << endl;
    l.deduplicate();
    l.traverse(print<int>);
    cout << endl;
    l.insert(l.search(1, l.size() - 1, l.last()), 3);
    l.traverse(print<int>);
    cout << endl;
    cout << endl;
}

int main() {
    test_List();
    return 0;
}