#include "HashTable.h"
#include <cstdio>

int main() {
    HashTable<int, int> h;
    h.put(2, 3);
    h.put(1, 4);
    printf("%d:%d", 2, *h.get(2));
    
    return 0;
}