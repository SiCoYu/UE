#ifndef __MSGBUFFER_H
#define __MSGBUFFER_H

/**
 * @brief 消息缓冲区
 */
class MsgBuffer
{
protected:
	MCircularBuffer* m_pMCircularBuffer;
	ByteBuffer* m_pHeaderBA;	// 主要是用来分析头的大小
	ByteBuffer* m_pRetBA;       // 返回的字节数组

protected:
	bool checkHasMsg();

public:
	MsgBuffer();
	~MsgBuffer();
};

#endif				// __MSGBUFFER_H