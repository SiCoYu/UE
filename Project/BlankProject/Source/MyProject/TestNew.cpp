#include <malloc.h>  
#include <iostream> 

void * __cdecl operator new(size_t size,
	const char *file, int line)
{
	void *ptr = (void *)malloc(size);
	return(ptr);
}

void __cdecl operator delete(void *p)
{
	free(p);
}