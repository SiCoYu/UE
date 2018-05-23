#pragma once

#include <string>

struct MyAllocRecordItem
{
protected:
	size_t bytes;
	unsigned int pool;
	std::string filename;
	size_t line;
	std::string function;

public:
	MyAllocRecordItem();
	MyAllocRecordItem(
		size_t sz, 
		unsigned int p, 
		const char* file, 
		size_t ln, 
		const char* func
	);
};