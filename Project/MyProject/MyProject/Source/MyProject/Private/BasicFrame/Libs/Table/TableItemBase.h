#ifndef __TableItemBase_H
#define __TableItemBase_H

#include "HAL/Platform.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TableItemHeader;
class TableItemBodyBase;
class MByteBuffer;

class TableItemBase : public GObject
{
public:
	TableItemHeader* mItemHeader;
    TableItemBodyBase* mItemBody;

public:
	TableItemBase();
	virtual void parseHeaderByteBuffer(MByteBuffer* bytes);

	template <class T>
	void parseBodyByteBuffer(MByteBuffer* bytes, uint32 offset);

	template <class T>
	void parseAllByteBuffer(MByteBuffer* bytes);
};

template <class T>
void TableItemBase::parseBodyByteBuffer(MByteBuffer* bytes, uint32 offset)
{
	if (nullptr == this->mItemBody)
	{
		this->mItemBody = (TableItemBodyBase *)MY_NEW T();
	}

	this->mItemBody->parseBodyByteBuffer(bytes, offset);
}

template <class T>
void TableItemBase::parseAllByteBuffer(MByteBuffer* bytes)
{
	// 解析头
	this->parseHeaderByteBuffer(bytes);
	// 保存下一个 Item 的头位置
	UtilTable::mPrePos = bytes->position;
	// 解析内容
	parseBodyByteBuffer<T>(bytes, this->mItemHeader->mOffset);
	// 移动到下一个 Item 头位置
	bytes->setPos(UtilTable::mPrePos);
}

MY_END_NAMESPACE

#endif