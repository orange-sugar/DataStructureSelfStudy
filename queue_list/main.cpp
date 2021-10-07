#include "queue_list.h"
#include "../_share/utils.h"
#include <iostream>

int main() {
    Print<int> Print;
    Queue<int> q;
    q.enqueue(2);
    q.enqueue(3);
    q.traverse(Print);
    q.dequeue();
    std::cout << q.front();
    return 0;
}