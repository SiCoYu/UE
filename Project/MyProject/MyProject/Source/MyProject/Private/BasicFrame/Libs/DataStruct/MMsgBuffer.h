#ifndef __MMsgBuffer_H
#define __MMsgBuffer_H

#include "BufferCV.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MCircularBuffer;
class MByteBuffer;

/**
 * @brief 消息缓冲区
 */
class MMsgBuffer : public GObject
{
	friend class MClientBuffer;

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
	MMsgBuffer(
		uint32 initCapacity = (uint32)BufferCV::eINIT_CAPACITY, 
		uint32 maxCapacity = (uint32)BufferCV::eMAX_CAPACITY
	);
	~MMsgBuffer();

	MByteBuffer* getHeaderBA();
	MByteBuffer* getMsgBodyBA();
	MCircularBuffer* getCircularBuffer();

	/**
	* @brief 获取前面的第一个完整的消息数据块
	*/
	bool popFront();
};

MY_END_NAMESPACE

#endif				// __MMsgBuffer_H