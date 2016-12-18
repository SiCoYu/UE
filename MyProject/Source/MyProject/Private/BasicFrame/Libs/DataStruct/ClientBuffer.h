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
	MsgBuffer* mRawBuffer;			// ֱ�Ӵӷ��������յ���ԭʼ�����ݣ�����ѹ���ͼ��ܹ�
	MsgBuffer* mMsgBuffer;			// ����ʹ�õĻ�����
	//ByteBuffer* mSendTmpBA;		// ������ʱ�����������͵����ݶ���ʱ��������
	MsgBuffer* mSendTmpBuffer;		// ������ʱ�����������͵����ݶ���ʱ��������
	ByteBuffer* mSocketSendBA;     // �������ͻ�����

	DynBuffer<char>* mDynBuffer;				// ���յ�����ʱ���ݣ���Ҫ�ŵ� mRawBuffer ��ȥ
	ByteBuffer* mUnCompressHeaderBA;	// ��Ž�ѹ���ͷ�ĳ���
	ByteBuffer* mSendData;				// ��Ž�Ҫ���͵����ݣ���Ҫ�ŵ� m_sendBuffer ��ȥ
	ByteBuffer* mTmpData;				// ��ʱ��Ҫת�������ݷ�������
	ByteBuffer* mTmp1fData;			// ��ʱ��Ҫת�������ݷ�������

	MMutex* mReadMutex;				// ������
	MMutex* mWriteMutex;				// д����

#if MSG_ENCRIPT
	CryptContext* mCryptContext;
#endif

public:
	ClientBuffer();
	~ClientBuffer();

	DynBuffer<char>* getDynBuffer();
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