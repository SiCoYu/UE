#pragma once

#include <new>	// nothrow_t
#include <stdlib.h>	// malloc, free
#include "MyMemoryDefaultAlloc.h"

class MyAllocatedObject
{
public:
	explicit MyAllocatedObject()
	{ }

	~MyAllocatedObject()
	{ }

	void* operator new(size_t sz, const char* file, int line, const char* func)
	{
		return MyDefaultAllocPolicy::allocateBytes(sz, file, line, func);
	}

	void* operator new(size_t sz)
	{
		return MyDefaultAllocPolicy::allocateBytes(sz);
	}

	void* operator new(size_t sz, void* ptr)
	{
		(void)sz;
		return ptr;
	}

	void* operator new[](size_t sz, const char* file, int line, const char* func)
	{
		return MyDefaultAllocPolicy::allocateBytes(sz, file, line, func);
	}

	void* operator new[](size_t sz)
	{
		return MyDefaultAllocPolicy::allocateBytes(sz);
	}

	void operator delete(void* ptr)
	{
		MyDefaultAllocPolicy::deallocateBytes(ptr);
	}

	void operator delete(void* ptr, void*)
	{
		MyDefaultAllocPolicy::deallocateBytes(ptr);
	}

	void operator delete(void* ptr, const char*, int, const char*)
	{
		MyDefaultAllocPolicy::deallocateBytes(ptr);
	}

	void operator delete[](void* ptr)
	{
		MyDefaultAllocPolicy::deallocateBytes(ptr);
	}

	void operator delete[](void* ptr, const char*, int, const char*)
	{
		MyDefaultAllocPolicy::deallocateBytes(ptr);
	}
};