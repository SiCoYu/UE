#pragma once

#include <new>	// nothrow_t
#include <stdlib.h>	// malloc, free

#ifdef new
#undef new
#endif

#ifdef delete
#undef delete
#endif

__forceinline void* operator new(size_t size);
__forceinline void* operator new(size_t size, const std::nothrow_t& noThrow);
__forceinline void* operator new[](size_t size);
__forceinline void* operator new[](size_t size, const std::nothrow_t& noThrow);
__forceinline void operator delete(void* ptr);
__forceinline void operator delete[](void* ptr);

#define my_new(type) new type
#define my_new_array(type,size) new type[size]
#define my_delete(ptr) delete ptr
#define my_delete_array(ptr) delete[] ptr