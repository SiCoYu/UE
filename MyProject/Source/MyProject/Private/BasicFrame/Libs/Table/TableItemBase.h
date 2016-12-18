#ifndef __TableItemBase_H_
#define __TableItemBase_H_

#include "HAL/Platform.h"

class TableItemHeader;
class TableItemBodyBase;
class ByteBuffer;

class TableItemBase
{
public:
	TableItemHeader* mItemHeader;
    TableItemBodyBase* mItemBody;

public:
	TableItemBase();
	virtual void parseHeaderByteBuffer(ByteBuffer* bytes);

	template <class T>
	void parseBodyByteBuffer(ByteBuffer* bytes, uint32 offset);

	template <class T>
	void parseAllByteBuffer(ByteBuffer* bytes);
};

template <class T>
void TableItemBase::parseBodyByteBuffer(ByteBuffer* bytes, uint32 offset)
{
	if (nullptr == mItemBody)
	{
		mItemBody = (TableItemBodyBase *)new T();
	}

	mItemBody->parseBodyByteBuffer(bytes, offset);
}

template <class T>
void TableItemBase::parseAllByteBuffer(ByteBuffer* bytes)
{
	// 解析头
	parseHeaderByteBuffer(bytes);
	// 保存下一个 Item 的头位置
	UtilTable::mPrePos = bytes->position;
	// 解析内容
	parseBodyByteBuffer<T>(bytes, mItemHeader->mOffset);
	// 移动到下一个 Item 头位置
	bytes->setPos(UtilTable::mPrePos);
}

#endif