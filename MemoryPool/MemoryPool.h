////////////////////////////////
/// usage : 1.	a simple memory pool supports allocating piece by piece and releasing as a whole only.
///         2.  it is basically a huge stack, so the pop operation is provided but it is very dangerous and deprecated.
/// 
/// note  : 1.	
////////////////////////////////

#ifndef SZX_CUTILIBS_MEMORY_POOL_H
#define SZX_CUTILIBS_MEMORY_POOL_H


typedef char Byte; // TODO[szx][0]: make sure (sizeof(Byte) == 1).
typedef Byte *Ptr;
typedef int Size;


static Size toByte(Size gb, Size mb, Size kb, Size b) {
    enum {
        B = 1,
        KB = 1024 * B,
        MB = 1024 * KB,
        GB = 1024 * MB
    };
    return ((gb * GB) + (mb * MB) + (kb *KB) + b);
}


#endif // SZX_CUTILIBS_MEMORY_POOL_H
