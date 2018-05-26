#include "MyProject.h"
#include "MyAllocatedObject.h"
#include "MClassFactory.h"

M_IMPLEMENT_CLASS(MyAllocatedObject, GObjectBase)
M_REGISTER_CLASS(MyAllocatedObject)

void* MyAllocatedObject::operator new(size_t sz, const char* file, int line, const char* func, MyMemoryConstructorFlag constructorFlag)
{
	return MyDefaultAllocPolicy::allocateBytes(sz, file, line, func);
}

void* MyAllocatedObject::operator new(size_t sz, MyMemoryConstructorFlag constructorFlag)
{
	return MyDefaultAllocPolicy::allocateBytes(sz);
}

void* MyAllocatedObject::operator new(size_t sz, void* ptr, MyMemoryConstructorFlag constructorFlag)
{
	(void)sz;
	return ptr;
}

void* MyAllocatedObject::operator new[](size_t sz, const char* file, int line, const char* func, MyMemoryConstructorFlag constructorFlag)
{
	return MyDefaultAllocPolicy::allocateBytes(sz, file, line, func);
}

void* MyAllocatedObject::operator new[](size_t sz, MyMemoryConstructorFlag constructorFlag)
{
	return MyDefaultAllocPolicy::allocateBytes(sz);
}

void MyAllocatedObject::operator delete(void* ptr)
{
	MyDefaultAllocPolicy::deallocateBytes(ptr);
}

void MyAllocatedObject::operator delete(void* ptr, void*)
{
	MyDefaultAllocPolicy::deallocateBytes(ptr);
}

void MyAllocatedObject::operator delete(void* ptr, const char*, int, const char*)
{
	MyDefaultAllocPolicy::deallocateBytes(ptr);
}

void MyAllocatedObject::operator delete[](void* ptr)
{
	MyDefaultAllocPolicy::deallocateBytes(ptr);
}

void MyAllocatedObject::operator delete[](void* ptr, const char*, int, const char*)
{
	MyDefaultAllocPolicy::deallocateBytes(ptr);
}