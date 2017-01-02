#pragma once

#ifdef new
#undef new
#endif

#ifdef delete
#undef delete
#endif

//------------------------------------------------------------------------------
/*
Override new / delete operators.
*/
//__forceinline void*
//operator new(size_t size)
//{
//	return Memory::Alloc(Memory::ObjectHeap, size);
//}
//
//__forceinline void*
//operator new(size_t size, const std::nothrow_t& noThrow)
//{
//	return Memory::Alloc(Memory::ObjectHeap, size);
//}
//
//__forceinline void*
//operator new[](size_t size)
//{
//	return Memory::Alloc(Memory::ObjectArrayHeap, size);
//}
//
//__forceinline void*
//operator new[](size_t size, const std::nothrow_t& noThrow)
//{
//	return Memory::Alloc(Memory::ObjectArrayHeap, size);
//}
//
//__forceinline void
//operator delete(void* p)
//{
//	Memory::Free(Memory::ObjectHeap, p);
//}
//
//__forceinline void
//operator delete[](void* p)
//{
//	Memory::Free(Memory::ObjectArrayHeap, p);
//}
//#endif


#define my_new(type) new type
#define my_new_array(type,size) new type[size]
#define my_delete(ptr) delete ptr
#define my_delete_array(ptr) delete[] ptr