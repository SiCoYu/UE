#include "MyProject.h"
#include "ClientBuffer.h"
#include "MsgBuffer.h"
#include "DynBuffer.h"
#include "MByteBuffer.h"
#include "MCircularBuffer.h"
#include "MMutex.h"
#include "MLock.h"
#include "Common.h"
#include "UtilStr.h"
#include "UtilMsg.h"

ClientBuffer::ClientBuffer()
{
	mRawBuffer = new MsgBuffer();
	mMsgBuffer = new MsgBuffer();
	//mSendTmpBA = new MByteBuffer();
	mSendTmpBuffer = new MsgBuffer();
	mSocketSendBA = new MByteBuffer();
	//mSocketSendBA.mId = 1000;

	//mDynBuffer = new DynamicBuffer<byte>(8096);
	mUnCompressHeaderBA = new MByteBuffer();
	mSendData = new MByteBuffer();
	mTmpData = new MByteBuffer(4);
	mTmp1fData = new MByteBuffer(4);

	mReadMutex = new MMutex();
	mWriteMutex = new MMutex();

#ifdef MSG_ENCRIPT
	mCryptContext = new CryptContext();
#endif
}

ClientBuffer::~ClientBuffer()
{
	delete mRawBuffer;
	delete mMsgBuffer;
	delete mSendTmpBuffer;

	delete mSocketSendBA;
	delete mUnCompressHeaderBA;
	delete mSendData;
	delete mTmpData;

	delete mReadMutex;
	delete mWriteMutex;

#ifdef MSG_ENCRIPT
	delete mCryptContext;
#endif
}

DynBuffer<char>* ClientBuffer::getDynBuffer()
{
	return mDynBuffer;
}


MsgBuffer* ClientBuffer::getSendTmpBuffer()
{
	return mSendTmpBuffer;
}

MByteBuffer* ClientBuffer::getSendBuffer()
{
	return mSocketSendBA;
}

MByteBuffer* ClientBuffer::getSendData()
{
	return mSendData;
}

#ifdef MSG_ENCRIPT
public void ClientBuffer::setCryptKey(byte[] encrypt)
{
	//mCryptContext.cryptAlgorithm = CryptAlgorithm.DES;
	mCryptContext.m_cryptKey = encrypt;
	Dec.DES_set_key_unchecked(mCryptContext.m_cryptKey, mCryptContext.m_cryptKeyArr[(int)CryptAlgorithm.DES] as DES_key_schedule);
}

public void ClientBuffer::checkDES()
{
	if (mCryptContext.m_cryptKey != null && mCryptContext.m_cryptAlgorithm != CryptAlgorithm.DES)
	{
		mCryptContext.m_cryptAlgorithm = CryptAlgorithm.DES;
	}
}
#endif

MsgBuffer* ClientBuffer::getRawBuffer()
{
	return mRawBuffer;
}

void ClientBuffer::SetRevBufferSize(int32 size)
{
	mDynBuffer = new DynBuffer<char>(size);
}

void ClientBuffer::moveDyn2Raw()
{
	GLogSys->log(UtilStr::Format("移动动态数据消息数据到原始数据队列，消息长度　{0}", mDynBuffer->getSize()));
	UtilMsg::formatBytes2Array(mDynBuffer->getBuffer(), mDynBuffer->getSize());

#ifdef MSG_ENCRIPT
	checkDES();
#endif
	// 接收到一个socket数据，就被认为是一个数据包，这个地方可能会有问题，服务器是这么发送的，只能这么处理，自己写入包的长度
	mTmp1fData->clear();
	mTmp1fData->writeUnsignedInt32(mDynBuffer->getSize());      // 填充长度
	mRawBuffer->getCircularBuffer()->pushBackBA(mTmp1fData);
	// 写入包的数据
	mRawBuffer->getCircularBuffer()->pushBackArr(mDynBuffer->getBuffer(), 0, mDynBuffer->getSize());
}

void ClientBuffer::moveRaw2Msg()
{
	while (mRawBuffer->popFront())  // 如果有数据
	{
		//UnCompressAndDecryptAllInOne();
		UnCompressAndDecryptEveryOne();
	}
}

void ClientBuffer::send(bool bnet)
{
	mTmpData->clear();
	mTmpData->writeUnsignedInt32(mSendData->getLength());      // 填充长度

	if (bnet)       // 从 socket 发送出去
	{
#ifdef NET_MULTHREAD
		using (MLock mlock = new MLock(mWriteMutex))
#endif
		{
			//mSendTmpBA.writeUnsignedInt(mSendData.length);                            // 写入头部长度
			//mSendTmpBA.writeBytes(mSendData.dynBuff.buff, 0, mSendData.length);      // 写入内容

			mSendTmpBuffer->getCircularBuffer()->pushBackBA(mTmpData);
			mSendTmpBuffer->getCircularBuffer()->pushBackBA(mSendData);
		}
	}
	else        // 直接放入接收消息缓冲区
	{
#ifdef NET_MULTHREAD

#endif
		{
			//mTmpData.clear();
			//mTmpData.writeUnsignedInt(mSendData.length);      // 填充长度

			mMsgBuffer->getCircularBuffer()->pushBackBA(mTmpData);              // 保存消息大小字段
			mMsgBuffer->getCircularBuffer()->pushBackBA(mSendData);             // 保存消息大小字段
		}
	}
}

MByteBuffer* ClientBuffer::getMsg()
{
	MLock mlock(mReadMutex);
	{
		if (mMsgBuffer->popFront())
		{
			return mMsgBuffer->getMsgBodyBA();
		}
	}

	return nullptr;
}

// 获取数据，然后压缩加密
void ClientBuffer::getSocketSendData()
{
	//mSocketSendBA.m_startTest = false;

	mSocketSendBA->clear();

	// 获取完数据，就解锁
#ifdef NET_MULTHREAD
	using (MLock mlock = new MLock(mWriteMutex))
#endif
	{
		//mSocketSendBA.writeBytes(mSendTmpBA.dynBuff.buff, 0, (uint)mSendTmpBA.length);
		//mSendTmpBA.clear();
		// 一次全部取出来发送出去
		//mSocketSendBA.writeBytes(mSendTmpBuffer.circuleBuffer.buff, 0, (uint)mSendTmpBuffer.circuleBuffer.size);
		//mSendTmpBuffer.circuleBuffer.clear();
		// 一次仅仅获取一个消息发送出去，因为每一个消息的长度要填写加密补位后的长度
		if (mSendTmpBuffer->popFront())     // 弹出一个消息，如果只有一个消息，内部会重置变量
		{
			mSocketSendBA->writeBytes(mSendTmpBuffer->getHeaderBA()->getDynBuffer()->getBuffer(), 0, mSendTmpBuffer->getHeaderBA()->getLength());       // 写入头
			mSocketSendBA->writeBytes(mSendTmpBuffer->getMsgBodyBA()->getDynBuffer()->getBuffer(), 0, mSendTmpBuffer->getMsgBodyBA()->getLength());             // 写入消息体
		}
	}

#if defined MSG_COMPRESS || defined MSG_ENCRIPT
	mSocketSendBA.setPos(0);
	CompressAndEncryptEveryOne();
	// CompressAndEncryptAllInOne();
#endif
	mSocketSendBA->setPos(0);        // 设置指针 pos

	//mSocketSendBA.m_startTest = true;
}

// 压缩加密每一个包
void ClientBuffer::CompressAndEncryptEveryOne()
{
	uint32 origMsgLen = 0;    // 原始的消息长度，后面判断头部是否添加压缩标志
	uint32 compressMsgLen = 0;
#ifdef MSG_ENCRIPT
	uint cryptLen = 0;
#endif
#if defined MSG_COMPRESS && !defined MSG_ENCRIPT
	bool bHeaderChange = false; // 消息内容最前面的四个字节中消息的长度是否需要最后修正
#endif
	while (mSocketSendBA->getBytesAvailable() > 0)
	{
#if defined MSG_COMPRESS && !defined MSG_ENCRIPT
		bHeaderChange = false;
#endif

		mSocketSendBA->readUnsignedInt32(origMsgLen);    // 读取一个消息包头

#ifdef MSG_COMPRESS
		if (origMsgLen > MsgCV::PACKET_ZIP_MIN)
		{
			compressMsgLen = mSocketSendBA->compress(origMsgLen);
		}
		else
		{
			mSocketSendBA->incPosDelta(origMsgLen);
			compressMsgLen = origMsgLen;
		}
#endif
		// 只加密消息 body
		//#if MSG_ENCRIPT
		//                mSocketSendBA.position -= compressMsgLen;      // 移动加密指针位置
		//                cryptLen = mSocketSendBA.encrypt(m_cryptKeyArr[(int)m_cryptAlgorithm], compressMsgLen, m_cryptAlgorithm);
		//                if (compressMsgLen != cryptLen)
		//                {
		//                    bHeaderChange = true;
		//                }
		//                compressMsgLen = cryptLen;
		//#endif

		// 加密如果系统补齐字节，长度可能会变成 8 字节的证书倍，因此需要等加密完成后再写入长度
#if defined MSG_COMPRESS && !defined MSG_ENCRIPT
		if (origMsgLen > DataCV::PACKET_ZIP_MIN)    // 如果原始长度需要压缩
		{
			bHeaderChange = true;
			origMsgLen = compressMsgLen;                // 压缩后的长度
			origMsgLen |= DataCV::PACKET_ZIP;            // 添加
		}
		//#endif
		//#if !MSG_ENCRIPT
		if (bHeaderChange)
		{
			mSocketSendBA->position -= (compressMsgLen + 4);        // 移动到头部位置
			mSocketSendBA->writeUnsignedInt32(origMsgLen, false);     // 写入压缩或者加密后的消息长度
			mSocketSendBA->incPosDelta(compressMsgLen);              // 移动到下一个位置
		}
#endif

		// 整个消息压缩后，包括 4 个字节头的长度，然后整个加密
#ifdef MSG_ENCRIPT
		cryptLen = ((compressMsgLen + 4 + 7) / 8) * 8 - 4;      // 计算加密后，不包括 4 个头长度的 body 长度
		if (origMsgLen > MsgCV::PACKET_ZIP_MIN)    // 如果原始长度需要压缩
		{
			origMsgLen = cryptLen;                // 压缩后的长度
			origMsgLen |= MsgCV::PACKET_ZIP;            // 添加
		}
		else
		{
			origMsgLen = cryptLen;                // 压缩后的长度
		}

		mSocketSendBA->decPosDelta((compressMsgLen + 4));        // 移动到头部位置
		mSocketSendBA->writeUnsignedInt32(origMsgLen, false);     // 写入压缩或者加密后的消息长度

		mSocketSendBA.decPosDelta(4);      // 移动到头部
		mSocketSendBA.encrypt(mCryptContext, 0);  // 加密
#endif
	}

	// 整个消息压缩后，包括 4 个字节头的长度，然后整个加密
	//#if MSG_ENCRIPT
	//mSocketSendBA.position = 0;      // 移动到头部
	//mSocketSendBA.encrypt(m_cryptKeyArr[(int)m_cryptAlgorithm], 0, m_cryptAlgorithm);
	//#endif
}

// 压缩解密作为一个包
void ClientBuffer::CompressAndEncryptAllInOne()
{
#ifdef MSG_COMPRESS
	uint origMsgLen = mSocketSendBA.length;       // 原始的消息长度，后面判断头部是否添加压缩标志
	uint compressMsgLen = 0;
	if (origMsgLen > MsgCV.PACKET_ZIP_MIN)
	{
		compressMsgLen = mSocketSendBA.compress();
	}
#endif

#ifdef MSG_ENCRIPT
	else
	{
		compressMsgLen = origMsgLen;
		mSocketSendBA.position += origMsgLen;
	}

	mSocketSendBA.position -= compressMsgLen;
	compressMsgLen = mSocketSendBA.encrypt(mCryptContext, 0);
#endif

#if defined MSG_COMPRESS || defined MSG_ENCRIPT             // 如果压缩或者加密，需要再次添加压缩或者加密后的头长度
	if (origMsgLen > MsgCV.PACKET_ZIP_MIN)    // 如果原始长度需要压缩
	{
		origMsgLen = compressMsgLen;
		origMsgLen |= MsgCV.PACKET_ZIP;            // 添加
	}
	else
	{
		origMsgLen = compressMsgLen;
	}

	mSocketSendBA.position = 0;
	mSocketSendBA.insertUnsignedInt32(origMsgLen);            // 写入压缩或者加密后的消息长度
#endif
}

// 消息格式
// |------------- 加密的整个消息  -------------------------------------|
// |----4 Header----|-压缩的 body----|----4 Header----|-压缩的 body----|
// |                |                |                |                |
void ClientBuffer::UnCompressAndDecryptEveryOne()
{
#ifdef MSG_ENCRIPT
	mRawBuffer.msgBodyBA.decrypt(mCryptContext, 0);
#endif
	//#if MSG_COMPRESS
	//mRawBuffer.headerBA.setPos(0); // 这个头目前没有用，是客户端自己添加的，服务器发送一个包，就认为是一个完整的包
	//mRawBuffer.msgBodyBA.setPos(0);
	//uint msglen = mRawBuffer.headerBA.readUnsignedInt();
	//if ((msglen & DataCV.PACKET_ZIP) > 0)
	//{
	//    mRawBuffer.msgBodyBA.uncompress();
	//}
	//#endif

	mRawBuffer->getMsgBodyBA()->setPos(0);

	uint32 msglen = 0;
	while (mRawBuffer->getMsgBodyBA()->getBytesAvailable() >= 4)
	{
		mRawBuffer->getMsgBodyBA()->readUnsignedInt32(msglen);    // 读取一个消息包头
		if (msglen == 0)     // 如果是 0 ，就说明最后是由于加密补齐的数据
		{
			break;
		}
#ifdef MSG_COMPRESS
		if ((msglen & MsgCV::PACKET_ZIP) > 0)
		{
			msglen &= (~MsgCV.PACKET_ZIP);         // 去掉压缩标志位
			Ctx.m_instance.m_logSys.log(string.Format("消息需要解压缩，消息未解压长度　{0}", msglen));
			msglen = mRawBuffer->getMsgBodyBA->uncompress(msglen);
			Ctx.m_instance.m_logSys.log(string.Format("消息需要解压缩，消息解压后长度　{0}", msglen));
		}
		else
#endif
		{
			GLogSys->log(UtilStr::Format("消息不需要解压缩，消息原始长度　{0}", msglen));
			mRawBuffer->getMsgBodyBA()->incPosDelta(msglen);
		}

		mUnCompressHeaderBA->clear();
		mUnCompressHeaderBA->writeUnsignedInt32(msglen);        // 写入解压后的消息的长度，不要写入 msglen ，如果压缩，再加密，解密后，再解压后的长度才是真正的长度
		mUnCompressHeaderBA->setPos(0);

#ifdef NET_MULTHREAD
		using (MLock mlock = new MLock(mReadMutex))
#endif
		{
			mMsgBuffer->getCircularBuffer()->pushBackBA(mUnCompressHeaderBA);             // 保存消息大小字段
			mMsgBuffer->getCircularBuffer()->pushBackArr(mRawBuffer->getMsgBodyBA()->getDynBuffer()->getBuffer(), mRawBuffer->getMsgBodyBA()->getPos() - msglen, msglen);      // 保存消息大小字段
		}

		GLogSys->log(UtilStr::Format("解压解密后消息起始索引 {0}, 消息长度　{1}, 消息 position 位置 {2}, 消息 size {3}", mRawBuffer->getMsgBodyBA()->getPos() - msglen, msglen, mRawBuffer->getMsgBodyBA()->getPos(), mRawBuffer->getMsgBodyBA()->getLength()));
		GNetDispList->addOneRevMsg();

		// Test 读取消息头
		// MByteBuffer buff = getMsg();
		// stNullUserCmd cmd = new stNullUserCmd();
		// cmd.derialize(buff);
		// Ctx.m_instance.m_logSys.log(string.Format("测试打印消息: byCmd = {0}, byParam = {1}", cmd.byCmd, cmd.byParam));
	}
}

void ClientBuffer::UnCompressAndDecryptAllInOne()
{
#ifdef MSG_ENCRIPT
	mRawBuffer.msgBodyBA.decrypt(mCryptContext, 0);
#endif
#ifdef MSG_COMPRESS
	mRawBuffer.headerBA.setPos(0);
	uint msglen = 0;
	mRawBuffer.headerBA.readUnsignedInt32(ref msglen);
	if ((msglen & MsgCV.PACKET_ZIP) > 0)
	{
		mRawBuffer.msgBodyBA.uncompress();
	}
#endif

#if !defined MSG_COMPRESS && !defined MSG_ENCRIPT
	mUnCompressHeaderBA->clear();
	mUnCompressHeaderBA->writeUnsignedInt32(mRawBuffer->getMsgBodyBA()->getLength());
	mUnCompressHeaderBA->setPos(0);
#endif
#ifdef NET_MULTHREAD
	using (MLock mlock = new MLock(mReadMutex))
#endif
	{
#if !defined MSG_COMPRESS && !defined MSG_ENCRIPT
		mMsgBuffer->getCircularBuffer()->pushBackBA(mUnCompressHeaderBA);             // 保存消息大小字段
#endif
		mMsgBuffer->getCircularBuffer()->pushBackBA(mRawBuffer->getMsgBodyBA());      // 保存消息大小字段
	}
}