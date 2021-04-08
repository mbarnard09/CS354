// allocation is too big to fit
#include <assert.h>
#include <stdlib.h>
#include "heapAlloc.h"
#include <stdio.h>

int main() {
    assert(initHeap(4096)  == 0);
    assert(allocHeap(1)    != NULL);
    assert(allocHeap(4095) == NULL);
    printf("%08x", (unsigned int)(allocHeap(4095)));
    exit(0);
}
