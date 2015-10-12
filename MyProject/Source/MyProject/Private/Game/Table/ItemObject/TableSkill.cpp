#include "MyProject.h"
#include "TableSkill.h"
#include "ByteBuffer.h"
#include "UtilTable.h"

void TableSkillItemBody::parseBodyByteBuffer(ByteBuffer* bytes, uint32 offset)
{
    bytes->setPos(offset);
	UtilTable::readString(bytes, m_name);
	UtilTable::readString(bytes, m_effect);
	bytes->readUnsignedInt32(m_skillAttackEffect);
	bytes->readInt32(m_bNeedMove);
}