#ifndef __NETCLIENTBUFFER_H
#define __NETCLIENTBUFFER_H

/**
* @brief ��Ϣ������
*/
class NetClientBuffer
{
protected:
	MsgBuffer* m_recvRawBuffer;     // ֱ�Ӵӷ��������յ���ԭʼ�����ݣ�����ѹ���ͼ��ܹ�
	MsgBuffer* m_recvMsgBuffer;		// ��ѹ���ܺ����ʹ�õĻ�����
	MsgBuffer* m_sendRawBuffer;		// ������ʱ�����������͵����ݶ���ʱ��������
	MsgBuffer* m_sendMsgBuffer;		// ���ͻ�������ѹ�����߼��ܹ���

	MCircularBuffer* m_dynBuff;        // ���յ�����ʱ���ݣ���Ҫ�ŵ� m_recvRawBuffer ��ȥ
	ByteBuffer* m_unCompressHeaderBA;  // ��Ž�ѹ���ͷ�ĳ���
	ByteBuffer* m_sendData;            // ��Ž�Ҫ���͵����ݣ���Ҫ�ŵ� m_sendBuffer ��ȥ
	ByteBuffer* m_tmpData;             // ��ʱ��Ҫת�������ݷ�������

public:
	NetClientBuffer();
	~NetClientBuffer();
};

#endif				// __NETCLIENTBUFFER_H