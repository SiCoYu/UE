#ifndef __MSGBUFFER_H
#define __MSGBUFFER_H

/**
 * @brief ��Ϣ������
 */
class MsgBuffer
{
protected:
	MCircularBuffer* m_pMCircularBuffer;
	ByteBuffer* m_pHeaderBA;	// ��Ҫ����������ͷ�Ĵ�С
	ByteBuffer* m_pRetBA;       // ���ص��ֽ�����

protected:
	bool checkHasMsg();

public:
	MsgBuffer();
	~MsgBuffer();
};

#endif				// __MSGBUFFER_H