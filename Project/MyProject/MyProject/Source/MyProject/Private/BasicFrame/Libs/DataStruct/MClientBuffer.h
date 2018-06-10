#ifndef __MClientBuffer_H
#define __MClientBuffer_H

#include "MyProject.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MMsgBuffer;
template <class T> class MDynBuffer;
class MByteBuffer;
class MCircularBuffer;
class MMutex;

/**
* @brief ��Ϣ������
*/
class MClientBuffer : public GObject
{
protected:
	MMsgBuffer* mRawBuffer;			// ֱ�Ӵӷ��������յ���ԭʼ�����ݣ�����ѹ���ͼ��ܹ�
	MMsgBuffer* mMsgBuffer;			// ����ʹ�õĻ�����
	//MByteBuffer* mSendTmpBA;		// ������ʱ�����������͵����ݶ���ʱ��������
	MMsgBuffer* mSendTmpBuffer;		// ������ʱ�����������͵����ݶ���ʱ��������
	MByteBuffer* mSocketSendBA;     // �������ͻ�����

	MDynBuffer<char>* mDynBuffer;				// ���յ�����ʱ���ݣ���Ҫ�ŵ� mRawBuffer ��ȥ
	MByteBuffer* mUnCompressHeaderBA;	// ��Ž�ѹ���ͷ�ĳ���
	MByteBuffer* mSendData;				// ��Ž�Ҫ���͵����ݣ���Ҫ�ŵ� m_sendBuffer ��ȥ
	MByteBuffer* mTmpData;				// ��ʱ��Ҫת�������ݷ�������
	MByteBuffer* mTmp1fData;			// ��ʱ��Ҫת�������ݷ�������

	MMutex* mReadMutex;				// ������
	MMutex* mWriteMutex;				// д����

#ifdef MSG_ENCRIPT
	CryptContext* mCryptContext;
#endif

public:
	MClientBuffer();
	~MClientBuffer();

	MDynBuffer<char>* getDynBuffer();
	MMsgBuffer* getSendTmpBuffer();
	MByteBuffer* getSendBuffer();
	MByteBuffer* getSendData();

#ifdef MSG_ENCRIPT
	void setCryptKey(byte[] encrypt)
	void checkDES()
#endif

	MMsgBuffer* getRawBuffer();
	void SetRevBufferSize(int32 size);
	void moveDyn2Raw();
	void moveRaw2Msg();
	void send(bool bnet = true);
	MByteBuffer* getMsg();
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

MY_END_NAMESPACE

#endif				// __MClientBuffer_H