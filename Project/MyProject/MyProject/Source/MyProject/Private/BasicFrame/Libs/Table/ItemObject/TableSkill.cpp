#include "MyProject.h"
#include "TableSkill.h"
#include "MByteBuffer.h"
#include "UtilTable.h"

TableSkillItemBody::TableSkillItemBody()
{
	
}

TableSkillItemBody::~TableSkillItemBody()
{
	
}

void TableSkillItemBody::parseBodyByteBuffer(MByteBuffer* bytes, uint32 offset)
{
    bytes->setPos(offset);
	UtilTable::readString(bytes, mName);
	UtilTable::readString(bytes, mEffect);
	bytes->readUnsignedInt32(mSkillAttackEffect);
	bytes->readInt32(mIsNeedMove);
}