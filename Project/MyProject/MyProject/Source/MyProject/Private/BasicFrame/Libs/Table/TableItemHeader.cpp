#include "MyProject.h"
#include "TableItemHeader.h"
#include "MByteBuffer.h"

// 解析头部
void TableItemHeader::parseHeaderByteBuffer(MByteBuffer* bytes)
{
	bytes->readUnsignedInt32(mId);
	bytes->readUnsignedInt32(mOffset);
}