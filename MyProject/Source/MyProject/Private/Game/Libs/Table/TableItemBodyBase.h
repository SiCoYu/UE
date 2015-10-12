#ifndef __TableItemBodyBase_H_
#define __TableItemBodyBase_H_

#include "MyProject.h"

class ByteBuffer;

class TableItemBodyBase
{
public:
    // 解析主要数据部分
	virtual void parseBodyByteBuffer(ByteBuffer* bytes, uint32 offset);
};

#endif