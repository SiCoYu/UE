#include "MyProject.h"
#include "TableObject.h"
#include "ByteBuffer.h"
#include "UtilTable.h"

void TableObjectItemBody::parseBodyByteArray(ByteBuffer* bytes, uint32 offset)
{
    bytes->position = offset;  // 从偏移处继续读取真正的内容
    m_name = UtilTable::readString(bytes);
	m_maxNum = bytes->readInt();
	m_type = bytes->readInt();
	m_color = bytes->readInt();
    m_prefab = UtilTable::readString(bytes as ByteArray);
}