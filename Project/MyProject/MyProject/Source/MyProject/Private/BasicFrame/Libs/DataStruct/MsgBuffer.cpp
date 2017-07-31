#include "MyProject.h"
#include "MsgBuffer.h"
#include "MCircularBuffer.h"
#include "ByteBuffer.h"
#include "MsgCV.h"

MsgBuffer::MsgBuffer(uint32 initCapacity, uint32 maxCapacity)
{
	mCircularBuffer = new MCircularBuffer(initCapacity, maxCapacity);
	mHeaderBA = new ByteBuffer();
	mMsgBodyBA = new ByteBuffer();
}

MsgBuffer::~MsgBuffer()
{
	delete mCircularBuffer;
	delete mHeaderBA;
	delete mMsgBodyBA;
}

ByteBuffer* MsgBuffer::getHeaderBA()
{
	return mHeaderBA;
}

ByteBuffer* MsgBuffer::getMsgBodyBA()
{
	return mMsgBodyBA;
}

MCircularBuffer* MsgBuffer::getCircularBuffer()
{
	return mCircularBuffer;
}

bool MsgBuffer::checkHasMsg()
{
	mCircularBuffer->frontBA(mHeaderBA, MsgCV::HEADER_SIZE);  // 将数据读取到 mHeaderBA
	uint32 msglen = 0;
	mHeaderBA->readUnsignedInt32(msglen);
#if MSG_COMPRESS
	if ((msglen & MsgCV::PACKET_ZIP) > 0)         // 如果有压缩标志
	{
		msglen &= (~MsgCV::PACKET_ZIP);         // 去掉压缩标志位
	}
#endif
	if (msglen <= mCircularBuffer->getSize() - MsgCV::HEADER_SIZE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
* @brief 获取前面的第一个完整的消息数据块
*/
bool MsgBuffer::popFront()
{
	bool ret = false;
	if (mCircularBuffer->getSize() > MsgCV::HEADER_SIZE)         // 至少要是 DataCV.HEADER_SIZE 大小加 1 ，如果正好是 DataCV.HEADER_SIZE ，那只能说是只有大小字段，没有内容
	{
		mCircularBuffer->frontBA(mHeaderBA, MsgCV::HEADER_SIZE);  // 如果不够整个消息的长度，还是不能去掉消息头的
		uint32 msglen = 0;
		mHeaderBA->readUnsignedInt32(msglen);
#if MSG_COMPRESS
		if ((msglen & MsgCV.PACKET_ZIP) > 0)         // 如果有压缩标志
		{
			msglen &= (~MsgCV.PACKET_ZIP);         // 去掉压缩标志位
		}
#endif

		if (msglen <= mCircularBuffer->getSize() - MsgCV::HEADER_SIZE)
		{
			mCircularBuffer->popFrontLen(MsgCV::HEADER_SIZE);
			mCircularBuffer->popFrontBA(mMsgBodyBA, msglen);
			ret = true;
		}
	}

	if (mCircularBuffer->empty())     // 如果已经清空，就直接重置
	{
		mCircularBuffer->clear();    // 读写指针从头开始，方式写入需要写入两部分
	}

	return ret;
}