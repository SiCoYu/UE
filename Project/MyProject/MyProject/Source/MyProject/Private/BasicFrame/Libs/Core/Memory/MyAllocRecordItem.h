#pragma once

#include <string>

struct MyAllocRecordItem
{
public:
	size_t mBytes;
	std::string mFileName;
	size_t mLine;
	std::string mFunction;

public:
	MyAllocRecordItem();
	MyAllocRecordItem(
		size_t sz,
		const char* file, 
		size_t ln, 
		const char* func
	);
};