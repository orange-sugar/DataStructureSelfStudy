#include "PQ_ComplHeap.h"
#include "../_share/UniPrint/print.h"

int main() {
    PQ_ComplHeap<int> pq;
    pq.insert(1);
    pq.insert(3);
    pq.insert(4);
    print(pq);
    return 0;
}