// a simple 8 byte allocation
#include <assert.h>
#include <stdlib.h>
#include "heapAlloc.h"
#include <stdio.h>

int main() {
    assert(initHeap(4096) == 0);
    void* ptr = allocHeap(8);
    printf("%08x", (unsigned int)(ptr));
    assert(ptr != NULL);
    exit(0);
}
