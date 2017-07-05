////////////////////////////////
/// usage : 1.	a simple memory pool supports allocating piece by piece and releasing as a whole only.
///         2.  it is basically a huge stack in heap, so the pop operation is provided but it is very dangerous and deprecated.
/// 
/// note  : 1.	
////////////////////////////////

#ifndef SZX_CUTILIBS_HEAP_STACK_H
#define SZX_CUTILIBS_HEAP_STACK_H


#include "MemoryPool.h"


typedef struct HeapStack {
    Ptr pool;
    Size used;
    Size size;
} HeapStack;


HeapStack* HeapStack_new(Size initCapacity);
void HeapStack_delete(HeapStack *hs);

void HeapStack_resize(HeapStack *hs, Size size);

// TODO[szx][0]: the pointer will be invalidated after resize.
//               return an offset to `pool` address as a handle instead!
//               and add an interface like `deref(pool, handle)` to get the real address.
// get a memory block from the pool.
Ptr HeapStack_alloc(HeapStack *hs, Size size);
Ptr HeapStack_push(HeapStack *hs, Size size);

// [deprecated]
// release a block of the most recently allocated memory.
void HeapStack_pop(HeapStack *hs, Size size);


#endif // SZX_CUTILIBS_HEAP_STACK_H
