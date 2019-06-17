#include "MyProject.h"
#include "TableObject.h"
#include "MByteBuffer.h"
#include "UtilTable.h"

MY_BEGIN_NAMESPACE(MyNS)

TableObjectItemBody::TableObjectItemBody()
{
	
}

TableObjectItemBody::~TableObjectItemBody()
{
	
}

void TableObjectItemBody::parseBodyByteBuffer(MByteBuffer* bytes, uint32 offset)
{
	bytes->setPos(offset);  // 从偏移处继续读取真正的内容
	UtilTable::readString(bytes, mName);
	bytes->readInt32(mMaxNum);
	bytes->readInt32(mType);
	bytes->readInt32(mColor);
	UtilTable::readString(bytes, mObjResName);
}

MY_END_NAMESPACE