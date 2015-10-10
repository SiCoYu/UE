#include "MyProject.h"
#include "MsgBuffer.h"
#include "MCircularBuffer.h"
#include "ByteBuffer.h"
#include "MsgCV.h"

public MsgBuffer(uint32 initCapacity, uint32 maxCapacity)
{
	m_circularBuffer = new MCircularBuffer(initCapacity, maxCapacity);
	m_headerBA = new ByteBuffer();
	m_msgBodyBA = new ByteBuffer();
}

MsgBuffer::~MsgBuffer()
{
	delete m_circularBuffer;
	delete m_headerBA;
	delete m_msgBodyBA;
}

ByteBuffer* MsgBuffer::getHeaderBA()
{
	return m_headerBA;
}

ByteBuffer* MsgBuffer::getMsgBodyBA()
{
	return m_msgBodyBA;
}

MCircularBuffer* MsgBuffer::getCircularBuffer()
{
	return m_circularBuffer;
}

bool MsgBuffer::checkHasMsg()
{
	m_circularBuffer->frontBA(m_headerBA, MsgCV.HEADER_SIZE);  // 将数据读取到 m_headerBA
	uint msglen = 0;
	m_headerBA->readUnsignedInt32(msglen);
#if MSG_COMPRESS
	if ((msglen & MsgCV.PACKET_ZIP) > 0)         // 如果有压缩标志
	{
		msglen &= (~MsgCV.PACKET_ZIP);         // 去掉压缩标志位
	}
#endif
	if (msglen <= m_circularBuffer->getSize() - MsgCV.HEADER_SIZE)
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
	if (m_circularBuffer->getSize() > MsgCV.HEADER_SIZE)         // 至少要是 DataCV.HEADER_SIZE 大小加 1 ，如果正好是 DataCV.HEADER_SIZE ，那只能说是只有大小字段，没有内容
	{
		m_circularBuffer->frontBA(m_headerBA, MsgCV.HEADER_SIZE);  // 如果不够整个消息的长度，还是不能去掉消息头的
		uint msglen = 0;
		m_headerBA->readUnsignedInt32(ref msglen);
#if MSG_COMPRESS
		if ((msglen & MsgCV.PACKET_ZIP) > 0)         // 如果有压缩标志
		{
			msglen &= (~MsgCV.PACKET_ZIP);         // 去掉压缩标志位
		}
#endif

		if (msglen <= m_circularBuffer->getSize() - MsgCV.HEADER_SIZE)
		{
			m_circularBuffer->popFrontLen(MsgCV.HEADER_SIZE);
			m_circularBuffer->popFrontBA(m_msgBodyBA, msglen);
			ret = true;
		}
	}

	if (m_circularBuffer->empty())     // 如果已经清空，就直接重置
	{
		m_circularBuffer->clear();    // 读写指针从头开始，方式写入需要写入两部分
	}

	return ret;
}