#pragma once

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

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

MY_END_NAMESPACE