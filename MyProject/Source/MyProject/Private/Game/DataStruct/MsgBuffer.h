#ifndef __MSGBUFFER_H
#define __MSGBUFFER_H

#include "BufferCV.h"

class MCircularBuffer;
class ByteBuffer;

/**
 * @brief 消息缓冲区
 */
class MsgBuffer
{
	friend class ClientBuffer;

protected:
	MCircularBuffer* m_circularBuffer;    // 环形缓冲区

	ByteBuffer* m_headerBA;     // 主要是用来分析头的大小
	ByteBuffer* m_msgBodyBA;        // 返回的字节数组

protected:
	/**
	* @brief 检查 CB 中是否有一个完整的消息
	*/
	bool checkHasMsg();

public:
	MsgBuffer(uint32 initCapacity = BufferCV.INIT_CAPACITY, uint32 maxCapacity = BufferCV.MAX_CAPACITY);
	~MsgBuffer();

	ByteBuffer* getHeaderBA();
	ByteBuffer* getMsgBodyBA();
	MCircularBuffer* getCircularBuffer();

	/**
	* @brief 获取前面的第一个完整的消息数据块
	*/
	bool popFront();
};

#endif				// __MSGBUFFER_H