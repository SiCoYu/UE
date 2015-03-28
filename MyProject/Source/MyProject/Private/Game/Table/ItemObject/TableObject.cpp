#include "MyProject.h"
#include "TableObject.h"
#include "ByteBuffer.h"
#include "UtilTable.h"

void TableObjectItemBody::parseBodyByteArray(ByteBuffer* bytes, uint32 offset)
{
	bytes->pos(offset);  // 从偏移处继续读取真正的内容
    m_name = UtilTable::readString(bytes);
	bytes->readInt32(m_maxNum);
	bytes->readInt32(m_type);
	bytes->readInt32(m_color);
    m_prefab = UtilTable::readString(bytes);
}