#ifndef __MyMemoryDefaultAlloc_H
#define __MyMemoryDefaultAlloc_H

#include <limits>	// std::numeric_limits

class MyDefaultAllocImpl
{
public:
    static void* allocBytes(size_t count, 
        const char* file, int line, const char* func);
    static void deallocBytes(void* ptr);
    static void* allocBytesAligned(size_t align, size_t count, 
        const char* file, int line, const char* func);
    static void deallocBytesAligned(size_t align, void* ptr);
};

class MyDefaultAllocPolicy
{
public:
    static inline void* allocateBytes(size_t count, 
        const char* file = 0, int line = 0, const char* func = 0)
    {
        return MyDefaultAllocImpl::allocBytes(count, file, line, func);
    }
    static inline void deallocateBytes(void* ptr)
    {
		MyDefaultAllocImpl::deallocBytes(ptr);
    }

    static inline size_t getMaxAllocationSize()
    {
        return std::numeric_limits<size_t>::max();
    }
private:
	MyDefaultAllocPolicy()
    { }
};

template <size_t Alignment = 0>
class MyDefaultAlignedAllocPolicy
{
public:
    typedef int IsValidAlignment
        [Alignment <= 128 && ((Alignment & (Alignment-1)) == 0) ? +1 : -1];

    static inline void* allocateBytes(size_t count, 
        const char* file = 0, int line = 0, const char* func = 0)
    {
        return NedAllocImpl::allocBytesAligned(Alignment, count, file, line, func);
    }

    static inline void deallocateBytes(void* ptr)
    {
        NedAllocImpl::deallocBytesAligned(Alignment, ptr);
    }

    static inline size_t getMaxAllocationSize()
    {
        return std::numeric_limits<size_t>::max();
    }
private:
	MyDefaultAlignedAllocPolicy()
    { }
};

#endif