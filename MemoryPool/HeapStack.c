#include "HeapStack.h"

#include <stdlib.h>


HeapStack* HeapStack_new(Size initCapacity) {
    HeapStack *hs = (HeapStack*)malloc(sizeof(HeapStack));
    hs->pool = (Ptr)malloc(initCapacity);
    hs->used = 0;
    hs->size = initCapacity;
    return hs;
}

void HeapStack_delete(HeapStack *hs) {
    free(hs->pool);
    free(hs);
}

void HeapStack_resize(HeapStack *hs, Size size) {
    hs->pool = (Ptr)realloc(hs->pool, size);
    hs->size = size;
}

static Size growthCapacity(HeapStack *hs) {
    return (hs->size *= 2);
}

Ptr HeapStack_alloc(HeapStack *hs, Size size) {
    Ptr p;
    if ((hs->used + size) > hs->size) {
        hs->pool = (Ptr)realloc(hs->pool, growthCapacity(hs));
    }
    p = hs->pool + hs->used;
    hs->used += size;
    return p;
}

Ptr HeapStack_push(HeapStack *hs, Size size) {
    return HeapStack_alloc(hs, size);
}

void HeapStack_pop(HeapStack *hs, Size size) {
    hs->used -= size;
}
