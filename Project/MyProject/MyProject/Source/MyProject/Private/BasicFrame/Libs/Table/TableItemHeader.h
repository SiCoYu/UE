#ifndef __TableItemHeader_H
#define __TableItemHeader_H

#include "MyProject.h"

class ByteBuffer;

class TableItemHeader
{
public:
    uint32 mId;              // 唯一 ID
    uint32 mOffset;           // 这一项在文件中的偏移

    // 解析头部
	virtual void parseHeaderByteBuffer(ByteBuffer* bytes);
};

#endif