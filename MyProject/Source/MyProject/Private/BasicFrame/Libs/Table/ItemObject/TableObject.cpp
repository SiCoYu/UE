#include "MyProject.h"
#include "TableObject.h"
#include "ByteBuffer.h"
#include "UtilTable.h"

void TableObjectItemBody::parseBodyByteBuffer(ByteBuffer* bytes, uint32 offset)
{
	bytes->setPos(offset);  // 从偏移处继续读取真正的内容
	UtilTable::readString(bytes, mName);
	bytes->readInt32(mMaxNum);
	bytes->readInt32(mType);
	bytes->readInt32(mColor);
	UtilTable::readString(bytes, mObjResName);
}