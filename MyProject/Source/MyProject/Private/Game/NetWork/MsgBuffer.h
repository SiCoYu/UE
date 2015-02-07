#ifndef __MSGBUFFER_H
#define __MSGBUFFER_H

class MCircularBuffer;
class ByteBuffer;

/**
 * @brief 消息缓冲区
 */
class MsgBuffer
{
protected:
	MCircularBuffer* m_pMCircularBuffer;
	ByteBuffer* m_pHeaderBA;	// 主要是用来分析头的大小的四个字节
	ByteBuffer* m_pMsgBA;       // 返回的字节数组，没有消息长度的一个完整的消息

protected:
	bool checkHasMsg();

public:
	MsgBuffer();
	~MsgBuffer();
};

#endif				// __MSGBUFFER_H