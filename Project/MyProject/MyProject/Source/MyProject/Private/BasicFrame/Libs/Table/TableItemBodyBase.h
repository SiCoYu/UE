#ifndef __TableItemBodyBase_H
#define __TableItemBodyBase_H

#include "MyProject.h"

class ByteBuffer;

class TableItemBodyBase
{
public:
    // 解析主要数据部分
	virtual void parseBodyByteBuffer(ByteBuffer* bytes, uint32 offset);
};

#endif