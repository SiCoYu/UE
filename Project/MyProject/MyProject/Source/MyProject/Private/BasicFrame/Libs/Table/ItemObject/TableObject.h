#ifndef __TableObject_H
#define __TableObject_H

#include <string>
#include "HAL/Platform.h"
#include "TableItemBodyBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TableObjectItemBody : TableItemBodyBase
{
public:
    std::string mName;
    int mMaxNum;
    int mType;
    int mColor;
	std::string mObjResName;

	TableObjectItemBody();
	virtual ~TableObjectItemBody();

	virtual void parseBodyByteBuffer(MByteBuffer* bytes, uint32 offset);
};

MY_END_NAMESPACE

#endif