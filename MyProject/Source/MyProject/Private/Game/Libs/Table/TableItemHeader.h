#ifndef __TableItemHeader_H_
#define __TableItemHeader_H_

#include "MyProject.h"

class ByteBuffer;

class TableItemHeader
{
public:
    uint32 m_uID;              // 唯一 ID
    uint32 m_offset;           // 这一项在文件中的偏移

    // 解析头部
	virtual void parseHeaderByteBuffer(ByteBuffer* bytes);
};

#endif