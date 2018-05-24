#pragma once

template<typename T>
T* constructN(T* basePtr, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		new ((void*)(basePtr + i)) T();
	}
	return basePtr;
}

#define MY_DEBUG_MODE 0
#if MY_DEBUG_MODE

#   define MY_MALLOC(bytes, category) MyDefaultAllocPolicy::allocateBytes(bytes, __FILE__, __LINE__, __FUNCTION__)

#   define MY_ALLOC_T(T, count, category) static_cast<T*>(MyDefaultAllocPolicy::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))

#   define MY_FREE(ptr, category) MyDefaultAllocPolicy::deallocateBytes((void*)ptr)

#   define MY_NEW_T(T, category) new (MyDefaultAllocPolicy::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T

#   define MY_NEW_ARRAY_T(T, count, category) ::Ogre::constructN(static_cast<T*>(MyDefaultAllocPolicy::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count) 

#   define MY_DELETE_T(ptr, T, category) if(ptr){(ptr)->~T(); MyDefaultAllocPolicy::deallocateBytes((void*)ptr);}

#   define MY_DELETE_ARRAY_T(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} MyDefaultAllocPolicy::deallocateBytes((void*)ptr);}

#   define OGRE_NEW new (__FILE__, __LINE__, __FUNCTION__)
#   define OGRE_DELETE delete

#else // !MY_DEBUG_MODE

#   define MY_MALLOC(bytes, category) MyDefaultAllocPolicy::allocateBytes(bytes)

#   define MY_ALLOC_T(T, count, category) static_cast<T*>(MyDefaultAllocPolicy::allocateBytes(sizeof(T)*(count)))

#   define MY_FREE(ptr, category) MyDefaultAllocPolicy::deallocateBytes((void*)ptr)

#   define MY_NEW_T(T, category) new (MyDefaultAllocPolicy::allocateBytes(sizeof(T))) T

#   define MY_NEW_ARRAY_T(T, count, category) ::Ogre::constructN(static_cast<T*>(MyDefaultAllocPolicy::allocateBytes(sizeof(T)*(count))), count) 

#   define MY_DELETE_T(ptr, T, category) if(ptr){(ptr)->~T(); MyDefaultAllocPolicy::deallocateBytes((void*)ptr);}

#   define MY_DELETE_ARRAY_T(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} MyDefaultAllocPolicy::deallocateBytes((void*)ptr);}

#   define OGRE_NEW new 
#   define OGRE_DELETE delete

template<typename T>
void deletePtr(T* ptr)
{
	MY_DELETE ptr;
}

#endif