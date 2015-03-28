#ifndef __TableItemBase_H_
#define __TableItemBase_H_

#include "MyProject.h"

class ByteBuffer;

class TableItemHeader
{
public:
    public uint32 m_uID;              // 唯一 ID
    public uint32 m_offset;           // 这一项在文件中的偏移

    // 解析头部
	virtual void parseHeaderByteArray(ByteBuffer* bytes);
};

#endif