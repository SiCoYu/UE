#include "MyProject.h"
#include "TableItemHeader.h"
#include "MByteBuffer.h"

MY_BEGIN_NAMESPACE(MyNS)

// 解析头部
void TableItemHeader::parseHeaderByteBuffer(MByteBuffer* bytes)
{
	bytes->readUnsignedInt32(mId);
	bytes->readUnsignedInt32(mOffset);
}

MY_END_NAMESPACE