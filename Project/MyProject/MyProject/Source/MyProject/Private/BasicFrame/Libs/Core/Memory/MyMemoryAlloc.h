#pragma once

//#include <new>	// nothrow_t
//#include <stdlib.h>	// malloc, free

#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryConstructorFlag.h"

//#ifdef new
//#undef new
//#endif
//
//#ifdef delete
//#undef delete
//#endif

/**
 * @brief ����û���������� new ������ new ����
 * @url http://en.cppreference.com/w/cpp/memory/new/operator_new
 * @brief The versions (1-4) are implicitly declared in each translation unit even if the <new> header is not included. Versions (1-8) are replaceable: a user-provided non-member function with the same signature defined anywhere in the program, in any source file, replaces the default version. Its declaration does not need to be visible.

The behavior is undefined if more than one replacement is provided in the program for any of the replaceable allocation function, or if a replacement is defined with the inline specifier. The program is ill-formed if a replacement is defined in namespace other than global namespace, or if it is defined as a static non-member function at global scope. 
 */
// error C4595: 'operator new': non-member operator new or delete functions may not be declared inline
//void* operator new(size_t size);
//__forceinline void* operator new(size_t size, const std::nothrow_t& noThrow);
//__forceinline void* operator new[](size_t size);
//__forceinline void* operator new[](size_t size, const std::nothrow_t& noThrow);
//__forceinline void operator delete(void* ptr);
//__forceinline void operator delete[](void* ptr);

void* operator new(size_t sz, const char* file, int line, const char* func, MyMemoryConstructorFlag constructorFlag);
void* operator new(size_t sz, MyMemoryConstructorFlag constructorFlag);
void* operator new(size_t sz, void* ptr, MyMemoryConstructorFlag constructorFlag);

void* operator new[](size_t sz, const char* file, int line, const char* func, MyMemoryConstructorFlag constructorFlag);
void* operator new[](size_t sz, MyMemoryConstructorFlag constructorFlag);

// delete û�����ص� MyMemoryConstructorFlag constructorFlag ������ UE4 �Ѿ����� delete �����ֻ�����������أ���Ϊ UE4 �Ѿ����� delete ���Լ������ٴ������ˣ������Ӳ��� , MyMemoryConstructorFlag constructorFlag ��������Ϊ UE4 ���ص������Ӵ�������Լ������� UE4 ��ʹ�ã�ȥ�� , MyMemoryConstructorFlag constructorFlag ����
// 2>G:\File\opensource\UnrealEngine-4.0\UE4Sample\MyProject2\Binaries\Win64\UE4Editor-MyProject2-Win64-Debug.dll : fatal error LNK1169: one or more multiply defined symbols found
// TestNew.cpp.obj : warning LNK4006 : "void __cdecl operator delete(void *)" (? ? 3@YAXPEAX@Z) already defined in MyProject2.cpp.obj; second definition ignored
// Creating library
void operator delete(void* ptr, MyMemoryConstructorFlag constructorFlag);
void operator delete(void* ptr, void*, MyMemoryConstructorFlag constructorFlag);

void operator delete(void* ptr, const char*, int, const char*, MyMemoryConstructorFlag constructorFlag);
void operator delete[](void* ptr, MyMemoryConstructorFlag constructorFlag);
void operator delete[](void* ptr, const char*, int, const char*, MyMemoryConstructorFlag constructorFlag);

// ��Ϊ UE4 ���� delete ����������ǻ������ͣ��Ͳ������������� delete �����ʱ�����ɾ�������������� delete [] ptr ���ͻᵽ UE4 dll �Ķ���ɾ�����ᵼ���ƻ��ѣ�����������ӿ�
template<class T>
void deleteBaseTypeArray(T* ptr, int count)
{
	MyDefaultAllocPolicy::deallocateBytes((void*)ptr);
}

//#define my_new(type) new type
//#define my_new_array(type,size) new type[size]
//#define my_delete(ptr) delete ptr
//#define my_delete_array(ptr) delete[] ptr

#define MY_DELETE_BASE_TYPE_ARRAY(ptr, T, count) \
	deleteBaseTypeArray(ptr, count);