#ifndef __TableItemBodyBase_H_
#define __TableItemBodyBase_H_

#include "MyProject.h"

class ByteArray;

class TableItemBodyBase
{
public:
    // 解析主要数据部分
	virtual void parseBodyByteArray(ByteArray* bytes, uint32 offset);
};

#endif