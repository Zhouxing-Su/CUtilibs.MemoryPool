#include "MonotonicMemoryPool.h"

#include <stdlib.h>


static Size Size_max(Size size0, Size size1) {
    return (size0 > size1) ? size0 : size1;
}


MemoryPage* MemoryPage_new(Size size, MemoryPage *prevPage) {
    MemoryPage *mp = (MemoryPage*)malloc(sizeof(MemoryPage));
    mp->page = (Ptr)malloc(size);
    mp->used = 0;
    mp->prev = prevPage;
    return mp;
}

void MemoryPage_delete(MemoryPage *mp) {
    free(mp->page);
    free(mp);
}

void MemoryPage_delete_recursive(MemoryPage *mp) {
    MemoryPage *prev = mp->prev;
    MemoryPage_delete(mp);
    if (prev != NULL) { MemoryPage_delete_recursive(prev); }
}


MonotonicMemoryPool* MonotonicMemoryPool_new(Size pageSize) {
    MonotonicMemoryPool *mmp = (MonotonicMemoryPool*)malloc(sizeof(MonotonicMemoryPool));
    mmp->pool = MemoryPage_new(pageSize, NULL);
    mmp->pageSize = pageSize;
    return mmp;
}

void MonotonicMemoryPool_delete(MonotonicMemoryPool *mmp) {
    MemoryPage_delete_recursive(mmp->pool);
    free(mmp);
}

Ptr MonotonicMemoryPool_alloc(MonotonicMemoryPool *mmp, Size size) {
    Ptr p;
    MemoryPage *mp = mmp->pool;
    if ((mp->used + size) > mmp->pageSize) {
        mp = MemoryPage_new(Size_max(mmp->pageSize, size), mp);
        mmp->pool = mp;
    }
    p = mp->page + mp->used;
    mp->used += size;
    return p;
}
