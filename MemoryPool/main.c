#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "HeapStack.h"
#include "MonotonicMemoryPool.h"


enum { BlockSize = 8, BlockNum = (1 << 24) };


void testHeapStack(Ptr *list) {
    int i;
    clock_t begin, mid, end;
    HeapStack *hs;

    begin = clock();
    hs = HeapStack_new(toByte(0, 0, 64, 0));
    for (i = 0; i < BlockNum; ++i) {
        list[i] = HeapStack_push(hs, BlockSize);
    }
    mid = clock();
    HeapStack_delete(hs);
    end = clock();
    printf("HeapStack(64K init): %d = %d + %d    %p\n", (end - begin), (mid - begin), (end - mid), list[rand()]);

    begin = clock();
    for (i = 0; i < BlockNum; ++i) {
        list[i] = malloc(BlockSize);
    }
    mid = clock();
    for (i = 0; i < BlockNum; ++i) {
        free(list[i]);
    }
    end = clock();
    printf("malloc&free: %d = %d + %d    %p\n", (end - begin), (mid - begin), (end - mid), list[rand()]);

    begin = clock();
    hs = HeapStack_new(toByte(0, 256, 0, 0));
    for (i = 0; i < BlockNum; ++i) {
        list[i] = HeapStack_push(hs, BlockSize);
    }
    mid = clock();
    HeapStack_delete(hs);
    end = clock();
    printf("HeapStack(256M init): %d = %d + %d    %p\n", (end - begin), (mid - begin), (end - mid), list[rand()]);
}

void testMonotonicMemoryPool(Ptr *list) {
    int i;
    clock_t begin, mid, end;
    MonotonicMemoryPool *mmp;

    begin = clock();
    mmp = MonotonicMemoryPool_new(toByte(0, 256, 0, 0));
    for (i = 0; i < BlockNum; ++i) {
        list[i] = MonotonicMemoryPool_alloc(mmp, BlockSize);
    }
    mid = clock();
    MonotonicMemoryPool_delete(mmp);
    end = clock();
    printf("MonotonicMemoryPool(64K page): %d = %d + %d    %p\n", (end - begin), (mid - begin), (end - mid), list[rand()]);

    begin = clock();
    for (i = 0; i < BlockNum; ++i) {
        list[i] = malloc(BlockSize);
    }
    mid = clock();
    for (i = 0; i < BlockNum; ++i) {
        free(list[i]);
    }
    end = clock();
    printf("malloc&free: %d = %d + %d    %p\n", (end - begin), (mid - begin), (end - mid), list[rand()]);

    begin = clock();
    mmp = MonotonicMemoryPool_new(toByte(0, 256, 0, 0));
    for (i = 0; i < BlockNum; ++i) {
        list[i] = MonotonicMemoryPool_alloc(mmp, BlockSize);
    }
    mid = clock();
    MonotonicMemoryPool_delete(mmp);
    end = clock();
    printf("MonotonicMemoryPool(256M page): %d = %d + %d    %p\n", (end - begin), (mid - begin), (end - mid), list[rand()]);
}


int main() {
    Ptr *list;

    srand((unsigned)time(NULL));
    list = (Ptr*)malloc(BlockNum * sizeof(Ptr));

    testHeapStack(list);
    testMonotonicMemoryPool(list);

    free(list);
    return 0;
}
