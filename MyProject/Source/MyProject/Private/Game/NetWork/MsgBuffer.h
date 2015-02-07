#ifndef __MSGBUFFER_H
#define __MSGBUFFER_H

class MCircularBuffer;
class ByteBuffer;

/**
 * @brief ��Ϣ������
 */
class MsgBuffer
{
protected:
	MCircularBuffer* m_pMCircularBuffer;
	ByteBuffer* m_pHeaderBA;	// ��Ҫ����������ͷ�Ĵ�С���ĸ��ֽ�
	ByteBuffer* m_pMsgBA;       // ���ص��ֽ����飬û����Ϣ���ȵ�һ����������Ϣ

protected:
	bool checkHasMsg();

public:
	MsgBuffer();
	~MsgBuffer();
};

#endif				// __MSGBUFFER_H