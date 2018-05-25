#pragma once
#include <malloc.h>  
#include <stddef.h>

class ClassNew
{
public:
	ClassNew();
	~ClassNew();

	//void* operator new(size_t size, const char *file, int line)
	//{
	//	return malloc(size);
	//}

};

