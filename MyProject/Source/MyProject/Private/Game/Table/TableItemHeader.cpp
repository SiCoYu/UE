#include "MyProject.h"
#include "TableItemBase.h"
#include "ByteBuffer.h"

// 解析头部
void TableItemBase::parseHeaderByteArray(ByteBuffer* bytes)
{
    m_uID = bytes->readUnsignedInt();
    m_offset = bytes->readUnsignedInt();
}