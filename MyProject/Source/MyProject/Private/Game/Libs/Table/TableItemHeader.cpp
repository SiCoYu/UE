#include "MyProject.h"
#include "TableItemHeader.h"
#include "ByteBuffer.h"

// 解析头部
void TableItemHeader::parseHeaderByteBuffer(ByteBuffer* bytes)
{
	bytes->readUnsignedInt32(m_uID);
	bytes->readUnsignedInt32(m_offset);
}