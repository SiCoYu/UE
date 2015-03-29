#include "MyProject.h"
#include "TableSkill.h"
#include "ByteBuffer.h"
#include "UtilTable.h"

void TableSkillItemBody::parseBodyByteArray(ByteBuffer* bytes, uint32 offset)
{
    bytes->pos(offset);
	UtilTable::readString(bytes, m_name);
	UtilTable::readString(bytes, m_effect);
	UtilTable::readString(bytes, m_desc);
}