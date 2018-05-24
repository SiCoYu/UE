#pragma once

#include <new>	// nothrow_t
#include <stdlib.h>	// malloc, free
#include "MyMemoryDefaultAlloc.h"

class AllocatedObject
{
public:
	explicit AllocatedObject()
	{ }

	~AllocatedObject()
	{ }

	void* operator new(size_t sz, const char* file, int line, const char* func)
	{
		return DefauleAllocPolicy::allocateBytes(sz, file, line, func);
	}

	void* operator new(size_t sz)
	{
		return DefauleAllocPolicy::allocateBytes(sz);
	}

	void* operator new(size_t sz, void* ptr)
	{
		(void)sz;
		return ptr;
	}

	void* operator new[](size_t sz, const char* file, int line, const char* func)
	{
		return DefauleAllocPolicy::allocateBytes(sz, file, line, func);
	}

	void* operator new[](size_t sz)
	{
		return DefauleAllocPolicy::allocateBytes(sz);
	}

	void operator delete(void* ptr)
	{
		DefauleAllocPolicy::deallocateBytes(ptr);
	}

	void operator delete(void* ptr, void*)
	{
		DefauleAllocPolicy::deallocateBytes(ptr);
	}

	void operator delete(void* ptr, const char*, int, const char*)
	{
		DefauleAllocPolicy::deallocateBytes(ptr);
	}

	void operator delete[](void* ptr)
	{
		DefauleAllocPolicy::deallocateBytes(ptr);
	}

	void operator delete[](void* ptr, const char*, int, const char*)
	{
		DefauleAllocPolicy::deallocateBytes(ptr);
	}
};