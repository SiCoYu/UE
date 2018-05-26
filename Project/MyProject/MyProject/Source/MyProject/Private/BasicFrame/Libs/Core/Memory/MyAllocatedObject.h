#pragma once

#include <new>	// nothrow_t
#include <stdlib.h>	// malloc, free
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryConstructorFlag.h"

class MyAllocatedObject
{
public:
	explicit MyAllocatedObject()
	{ }

	~MyAllocatedObject()
	{ }

	void* operator new(size_t sz, const char* file, int line, const char* func, MyMemoryConstructorFlag constructorFlag);
	void* operator new(size_t sz, MyMemoryConstructorFlag constructorFlag);
	void* operator new(size_t sz, void* ptr, MyMemoryConstructorFlag constructorFlag);
	void* operator new[](size_t sz, const char* file, int line, const char* func, MyMemoryConstructorFlag constructorFlag);
	void* operator new[](size_t sz, MyMemoryConstructorFlag constructorFlag);
	void operator delete(void* ptr, MyMemoryConstructorFlag constructorFlag);
	void operator delete(void* ptr, void*, MyMemoryConstructorFlag constructorFlag);
	void operator delete(void* ptr, const char*, int, const char*, MyMemoryConstructorFlag constructorFlag);
	void operator delete[](void* ptr, MyMemoryConstructorFlag constructorFlag);
	void operator delete[](void* ptr, const char*, int, const char*, MyMemoryConstructorFlag constructorFlag);
};