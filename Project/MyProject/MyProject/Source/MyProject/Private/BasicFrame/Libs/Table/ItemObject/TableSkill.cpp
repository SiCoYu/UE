#include "MyProject.h"
#include "TableSkill.h"
#include "MByteBuffer.h"
#include "UtilTable.h"

MY_BEGIN_NAMESPACE(MyNS)

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

MY_END_NAMESPACE