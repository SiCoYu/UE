#pragma once

#include <new>	// nothrow_t
#include <stdlib.h>	// malloc, free
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryConstructorFlag.h"
#include "GObjectBase.h"
#include "MClassInfo.h"
#include "MMutex.h"
#include "MClassMacros.h"
#include "BaseClassDef.h"

class MyAllocatedObject : public GObjectBase
{
	M_DECLARE_CLASS(MyAllocatedObject)
	M_DECLARE_SUPER_KW(GObjectBase)

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
	void operator delete(void* ptr);
	void operator delete(void* ptr, void*);
	void operator delete(void* ptr, const char*, int, const char*);
	void operator delete[](void* ptr);
	void operator delete[](void* ptr, const char*, int, const char*);
};