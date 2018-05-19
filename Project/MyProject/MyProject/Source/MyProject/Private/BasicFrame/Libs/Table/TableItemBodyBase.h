#ifndef __TableItemBodyBase_H
#define __TableItemBodyBase_H

#include "MyProject.h"

class MByteBuffer;

class TableItemBodyBase
{
public:
    // 解析主要数据部分
	virtual void parseBodyByteBuffer(MByteBuffer* bytes, uint32 offset);
};

#endif