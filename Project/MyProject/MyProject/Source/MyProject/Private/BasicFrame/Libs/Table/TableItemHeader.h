#ifndef __TableItemHeader_H
#define __TableItemHeader_H

#include "MyProject.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MByteBuffer;

class TableItemHeader : public GObject
{
public:
    uint32 mId;              // 唯一 Id
    uint32 mOffset;           // 这一项在文件中的偏移

    // 解析头部
	virtual void parseHeaderByteBuffer(MByteBuffer* bytes);
};

MY_END_NAMESPACE

#endif