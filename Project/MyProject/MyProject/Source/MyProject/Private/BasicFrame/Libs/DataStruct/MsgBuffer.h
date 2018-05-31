#ifndef __MsgBuffer_H
#define __MsgBuffer_H

#include "BufferCV.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MCircularBuffer;
class MByteBuffer;

/**
 * @brief 消息缓冲区
 */
class MsgBuffer
{
	friend class ClientBuffer;

protected:
	MCircularBuffer* mCircularBuffer;    // 环形缓冲区

	MByteBuffer* mHeaderBA;     // 主要是用来分析头的大小
	MByteBuffer* mMsgBodyBA;        // 返回的字节数组

protected:
	/**
	* @brief 检查 CB 中是否有一个完整的消息
	*/
	bool checkHasMsg();

public:
	MsgBuffer(uint32 initCapacity = BufferCV::INIT_CAPACITY, uint32 maxCapacity = BufferCV::MAX_CAPACITY);
	~MsgBuffer();

	MByteBuffer* getHeaderBA();
	MByteBuffer* getMsgBodyBA();
	MCircularBuffer* getCircularBuffer();

	/**
	* @brief 获取前面的第一个完整的消息数据块
	*/
	bool popFront();
};

MY_END_NAMESPACE

#endif				// __MsgBuffer_H