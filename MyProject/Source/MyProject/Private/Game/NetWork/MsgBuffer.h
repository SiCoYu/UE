#ifndef __MSGBUFFER_H
#define __MSGBUFFER_H

#define MSGHEADERSIZE 4;   // ������ռ�ݼ����ֽ�

class MCircularBuffer;
class ByteBuffer;

/**
 * @brief ��Ϣ������
 */
class MsgBuffer
{
	friend class NetClientBuffer;

protected:
	MCircularBuffer* m_pMCircularBuffer;
	ByteBuffer* m_pHeaderBA;	// ��Ҫ����������ͷ�Ĵ�С���ĸ��ֽ�
	ByteBuffer* m_pMsgBA;       // ���ص��ֽ����飬û����Ϣ���ȵ�һ����������Ϣ
	uint32 m_msgLen;			// һ����Ϣ�ĳ���

public:
	MsgBuffer();
	~MsgBuffer();
	bool checkHasMsg();
	bool moveOutOneMsg();
};

#endif				// __MSGBUFFER_H