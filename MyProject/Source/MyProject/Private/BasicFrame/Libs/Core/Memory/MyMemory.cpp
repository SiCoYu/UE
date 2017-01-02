#include "MyProject.h"
#include "MyMemory.h"

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