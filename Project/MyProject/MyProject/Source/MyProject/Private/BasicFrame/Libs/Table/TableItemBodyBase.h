#ifndef __TableItemBodyBase_H
#define __TableItemBodyBase_H

#include "MyProject.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MByteBuffer;

class TableItemBodyBase : public GObject
{
public:
    // 解析主要数据部分
	virtual void parseBodyByteBuffer(MByteBuffer* bytes, uint32 offset);
};

MY_END_NAMESPACE

#endif