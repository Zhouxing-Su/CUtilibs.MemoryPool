////////////////////////////////
/// usage : 1.	a simple memory pool supports allocating piece by piece and releasing as a whole only.
///         2.  it is basically a huge stack with a series of memory pages managed by a linked list.
/// 
/// note  : 1.	
////////////////////////////////

#ifndef SZX_CUTILIBS_MONOTONIC_MEMORY_POOL_H
#define SZX_CUTILIBS_MONOTONIC_MEMORY_POOL_H


#include "MemoryPool.h"


typedef struct MemoryPage {
    Ptr page;
    Size used;

    struct MemoryPage *prev;
} MemoryPage;

typedef struct MonotonicMemoryPool {
    MemoryPage *pool;
    Size pageSize;
} MonotonicMemoryPool;


MemoryPage* MemoryPage_new(Size size, MemoryPage *prevPage);
void MemoryPage_delete(MemoryPage *mp);
void MemoryPage_delete_recursive(MemoryPage *mp);


MonotonicMemoryPool* MonotonicMemoryPool_new(Size pageSize);
void MonotonicMemoryPool_delete(MonotonicMemoryPool *mmp);

// get a memory block from the pool.
Ptr MonotonicMemoryPool_alloc(MonotonicMemoryPool *mmp, Size size);


#endif // SZX_CUTILIBS_MONOTONIC_MEMORY_POOL_H
