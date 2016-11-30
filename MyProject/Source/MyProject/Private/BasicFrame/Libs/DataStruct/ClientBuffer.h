#ifndef __CLIENTBUFFER_H
#define __CLIENTBUFFER_H

#include "MyProject.h"
#include "PlatformDefine.h"

class MsgBuffer;
template <class T> class DynBuffer;
class ByteBuffer;
class MCircularBuffer;
class MMutex;

/**
* @brief ��Ϣ������
*/
class ClientBuffer
{
protected:
	MsgBuffer* m_rawBuffer;			// ֱ�Ӵӷ��������յ���ԭʼ�����ݣ�����ѹ���ͼ��ܹ�
	MsgBuffer* m_msgBuffer;			// ����ʹ�õĻ�����
	//ByteBuffer* m_sendTmpBA;		// ������ʱ�����������͵����ݶ���ʱ��������
	MsgBuffer* m_sendTmpBuffer;		// ������ʱ�����������͵����ݶ���ʱ��������
	ByteBuffer* m_socketSendBA;     // �������ͻ�����

	DynBuffer<char>* m_dynBuff;				// ���յ�����ʱ���ݣ���Ҫ�ŵ� m_rawBuffer ��ȥ
	ByteBuffer* m_unCompressHeaderBA;	// ��Ž�ѹ���ͷ�ĳ���
	ByteBuffer* m_sendData;				// ��Ž�Ҫ���͵����ݣ���Ҫ�ŵ� m_sendBuffer ��ȥ
	ByteBuffer* m_tmpData;				// ��ʱ��Ҫת�������ݷ�������
	ByteBuffer* m_tmp1fData;			// ��ʱ��Ҫת�������ݷ�������

	MMutex* m_readMutex;				// ������
	MMutex* m_writeMutex;				// д����

#if MSG_ENCRIPT
	CryptContext* m_cryptContext;
#endif

public:
	ClientBuffer();
	~ClientBuffer();

	DynBuffer<char>* getDynBuff();
	MsgBuffer* getSendTmpBuffer();
	ByteBuffer* getSendBuffer();
	ByteBuffer* getSendData();

#if MSG_ENCRIPT
	void setCryptKey(byte[] encrypt)
	void checkDES()
#endif

	MsgBuffer* getRawBuffer();
	void SetRevBufferSize(int32 size);
	void moveDyn2Raw();
	void moveRaw2Msg();
	void send(bool bnet = true);
	ByteBuffer* getMsg();
	// ��ȡ���ݣ�Ȼ��ѹ������
	void getSocketSendData();

protected:
	// ѹ������ÿһ����
	void CompressAndEncryptEveryOne();
	// ѹ��������Ϊһ����
	void CompressAndEncryptAllInOne();
	// ��Ϣ��ʽ
	// |------------- ���ܵ�������Ϣ  -------------------------------------|
	// |----4 Header----|-ѹ���� body----|----4 Header----|-ѹ���� body----|
	// |                |                |                |                |
	void UnCompressAndDecryptEveryOne();
	void UnCompressAndDecryptAllInOne();
};

#endif				// __NETCLIENTBUFFER_H