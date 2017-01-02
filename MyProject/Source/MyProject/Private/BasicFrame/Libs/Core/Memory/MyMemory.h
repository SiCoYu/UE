#pragma once

#include <new>	// nothrow_t
#include <stdlib.h>	// malloc, free

#ifdef new
#undef new
#endif

#ifdef delete
#undef delete
#endif

__forceinline void* operator new(size_t size)
{
	//return Memory::Alloc(Memory::ObjectHeap, size);
	void* ptr = malloc(size);
	return ptr;
}

__forceinline void* operator new(size_t size, const std::nothrow_t& noThrow)
{
	//return Memory::Alloc(Memory::ObjectHeap, size);
	void* ptr = malloc(size);
	return ptr;
}

__forceinline void* operator new[](size_t size)
{
	//return Memory::Alloc(Memory::ObjectArrayHeap, size);
	void* ptr = malloc(size);
	return ptr;
}

__forceinline void* operator new[](size_t size, const std::nothrow_t& noThrow)
{
	//return Memory::Alloc(Memory::ObjectArrayHeap, size);
	void* ptr = malloc(size);
	return ptr;
}

__forceinline void operator delete(void* ptr)
{
	//Memory::Free(Memory::ObjectHeap, ptr);
	free(ptr);
}

__forceinline void operator delete[](void* ptr)
{
	//Memory::Free(Memory::ObjectArrayHeap, ptr);
	free(ptr);
}


#define my_new(type) new type
#define my_new_array(type,size) new type[size]
#define my_delete(ptr) delete ptr
#define my_delete_array(ptr) delete[] ptr