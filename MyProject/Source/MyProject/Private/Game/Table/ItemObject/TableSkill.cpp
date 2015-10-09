#include "MyProject.h"
#include "TableSkill.h"
#include "ByteBuffer.h"
#include "UtilTable.h"

void TableSkillItemBody::parseBodyByteArray(ByteBuffer* bytes, uint32 offset)
{
    bytes->setPos(offset);
	UtilTable::readString(bytes, m_name);
	UtilTable::readString(bytes, m_effect);
	UtilTable::readString(bytes, m_desc);
}