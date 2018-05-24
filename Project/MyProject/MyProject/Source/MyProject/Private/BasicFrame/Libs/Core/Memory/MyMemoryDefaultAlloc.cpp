#include "MyProject.h"
#include "MyMemoryDefaultAlloc.h"
#include <stdlib.h>	// malloc, free
#include "MyMemoryTracker.h"

#define MY_MEMORY_TRACKER 1

void* DefauleAllocImpl::allocBytes(size_t count,
    const char* file, int line, const char* func)
{
    void* ptr = malloc(count);
#if MY_MEMORY_TRACKER
	MyMemoryTracker::get()._recordAlloc(ptr, count, file, line, func);
#endif
    return ptr;
}

void DefauleAllocImpl::deallocBytes(void* ptr)
{
    if (!ptr)
        return;
#if MY_MEMORY_TRACKER
	MyMemoryTracker::get()._recordDealloc(ptr);
#endif
	free(ptr);
}

void* DefauleAllocImpl::allocBytesAligned(size_t align, size_t count,
    const char* file, int line, const char* func)
{
    void* ptr = _aligned_malloc(count, align);
#if MY_MEMORY_TRACKER
	MyMemoryTracker::get()._recordAlloc(ptr, count, file, line, func);
#endif
    return ptr;
}

void DefauleAllocImpl::deallocBytesAligned(size_t align, void* ptr)
{
    if (!ptr)
        return;
#if MY_MEMORY_TRACKER
	MyMemoryTracker::get()._recordDealloc(ptr);
#endif
	_aligned_free(ptr);
}