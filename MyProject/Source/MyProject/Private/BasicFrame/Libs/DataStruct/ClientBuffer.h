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
* @brief 消息缓冲区
*/
class ClientBuffer
{
protected:
	MsgBuffer* mRawBuffer;			// 直接从服务器接收到的原始的数据，可能压缩和加密过
	MsgBuffer* mMsgBuffer;			// 可以使用的缓冲区
	//ByteBuffer* mSendTmpBA;		// 发送临时缓冲区，发送的数据都暂时放在这里
	MsgBuffer* mSendTmpBuffer;		// 发送临时缓冲区，发送的数据都暂时放在这里
	ByteBuffer* mSocketSendBA;     // 真正发送缓冲区

	DynBuffer<char>* mDynBuffer;				// 接收到的临时数据，将要放到 mRawBuffer 中去
	ByteBuffer* mUnCompressHeaderBA;	// 存放解压后的头的长度
	ByteBuffer* mSendData;				// 存放将要发送的数据，将要放到 m_sendBuffer 中去
	ByteBuffer* mTmpData;				// 临时需要转换的数据放在这里
	ByteBuffer* mTmp1fData;			// 临时需要转换的数据放在这里

	MMutex* mReadMutex;				// 读互斥
	MMutex* mWriteMutex;				// 写互斥

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
	// 获取数据，然后压缩加密
	void getSocketSendData();

protected:
	// 压缩加密每一个包
	void CompressAndEncryptEveryOne();
	// 压缩解密作为一个包
	void CompressAndEncryptAllInOne();
	// 消息格式
	// |------------- 加密的整个消息  -------------------------------------|
	// |----4 Header----|-压缩的 body----|----4 Header----|-压缩的 body----|
	// |                |                |                |                |
	void UnCompressAndDecryptEveryOne();
	void UnCompressAndDecryptAllInOne();
};

#endif				// __NETCLIENTBUFFER_H