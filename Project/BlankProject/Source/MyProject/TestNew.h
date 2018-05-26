#include <malloc.h>  
#include <iostream>  

using namespace std;

void * __cdecl operator new(size_t size,
	const char *file, int line);

void __cdecl operator delete(void *p);

#define new new(__FILE__, __LINE__)