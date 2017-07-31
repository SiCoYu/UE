#include "MyProject.h"
#include "ClientBuffer.h"
#include "MsgBuffer.h"
#include "DynBuffer.h"
#include "ByteBuffer.h"
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
	//mSendTmpBA = new ByteBuffer();
	mSendTmpBuffer = new MsgBuffer();
	mSocketSendBA = new ByteBuffer();
	//mSocketSendBA.mId = 1000;

	//mDynBuffer = new DynamicBuffer<byte>(8096);
	mUnCompressHeaderBA = new ByteBuffer();
	mSendData = new ByteBuffer();
	mTmpData = new ByteBuffer(4);
	mTmp1fData = new ByteBuffer(4);

	mReadMutex = new MMutex();
	mWriteMutex = new MMutex();

#if MSG_ENCRIPT
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

#if MSG_ENCRIPT
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

ByteBuffer* ClientBuffer::getSendBuffer()
{
	return mSocketSendBA;
}

ByteBuffer* ClientBuffer::getSendData()
{
	return mSendData;
}

#if MSG_ENCRIPT
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
	GLogSys->log(UtilStr::Format("�ƶ���̬������Ϣ���ݵ�ԭʼ���ݶ��У���Ϣ���ȡ�{0}", mDynBuffer->getSize()));
	UtilMsg::formatBytes2Array(mDynBuffer->getBuffer(), mDynBuffer->getSize());

#if MSG_ENCRIPT
	checkDES();
#endif
	// ���յ�һ��socket���ݣ��ͱ���Ϊ��һ�����ݰ�������ط����ܻ������⣬����������ô���͵ģ�ֻ����ô�����Լ�д����ĳ���
	mTmp1fData->clear();
	mTmp1fData->writeUnsignedInt32(mDynBuffer->getSize());      // ��䳤��
	mRawBuffer->getCircularBuffer()->pushBackBA(mTmp1fData);
	// д���������
	mRawBuffer->getCircularBuffer()->pushBackArr(mDynBuffer->getBuffer(), 0, mDynBuffer->getSize());
}

void ClientBuffer::moveRaw2Msg()
{
	while (mRawBuffer->popFront())  // ���������
	{
		//UnCompressAndDecryptAllInOne();
		UnCompressAndDecryptEveryOne();
	}
}

void ClientBuffer::send(bool bnet)
{
	mTmpData->clear();
	mTmpData->writeUnsignedInt32(mSendData->getLength());      // ��䳤��

	if (bnet)       // �� socket ���ͳ�ȥ
	{
#if NET_MULTHREAD
		using (MLock mlock = new MLock(mWriteMutex))
#endif
		{
			//mSendTmpBA.writeUnsignedInt(mSendData.length);                            // д��ͷ������
			//mSendTmpBA.writeBytes(mSendData.dynBuff.buff, 0, mSendData.length);      // д������

			mSendTmpBuffer->getCircularBuffer()->pushBackBA(mTmpData);
			mSendTmpBuffer->getCircularBuffer()->pushBackBA(mSendData);
		}
	}
	else        // ֱ�ӷ��������Ϣ������
	{
#if NET_MULTHREAD

#endif
		{
			//mTmpData.clear();
			//mTmpData.writeUnsignedInt(mSendData.length);      // ��䳤��

			mMsgBuffer->getCircularBuffer()->pushBackBA(mTmpData);              // ������Ϣ��С�ֶ�
			mMsgBuffer->getCircularBuffer()->pushBackBA(mSendData);             // ������Ϣ��С�ֶ�
		}
	}
}

ByteBuffer* ClientBuffer::getMsg()
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

// ��ȡ���ݣ�Ȼ��ѹ������
void ClientBuffer::getSocketSendData()
{
	//mSocketSendBA.m_startTest = false;

	mSocketSendBA->clear();

	// ��ȡ�����ݣ��ͽ���
#if NET_MULTHREAD
	using (MLock mlock = new MLock(mWriteMutex))
#endif
	{
		//mSocketSendBA.writeBytes(mSendTmpBA.dynBuff.buff, 0, (uint)mSendTmpBA.length);
		//mSendTmpBA.clear();
		// һ��ȫ��ȡ�������ͳ�ȥ
		//mSocketSendBA.writeBytes(mSendTmpBuffer.circuleBuffer.buff, 0, (uint)mSendTmpBuffer.circuleBuffer.size);
		//mSendTmpBuffer.circuleBuffer.clear();
		// һ�ν�����ȡһ����Ϣ���ͳ�ȥ����Ϊÿһ����Ϣ�ĳ���Ҫ��д���ܲ�λ��ĳ���
		if (mSendTmpBuffer->popFront())     // ����һ����Ϣ�����ֻ��һ����Ϣ���ڲ������ñ���
		{
			mSocketSendBA->writeBytes(mSendTmpBuffer->getHeaderBA()->getDynBuffer()->getBuffer(), 0, mSendTmpBuffer->getHeaderBA()->getLength());       // д��ͷ
			mSocketSendBA->writeBytes(mSendTmpBuffer->getMsgBodyBA()->getDynBuffer()->getBuffer(), 0, mSendTmpBuffer->getMsgBodyBA()->getLength());             // д����Ϣ��
		}
	}

#if MSG_COMPRESS || MSG_ENCRIPT
	mSocketSendBA.setPos(0);
	CompressAndEncryptEveryOne();
	// CompressAndEncryptAllInOne();
#endif
	mSocketSendBA->setPos(0);        // ����ָ�� pos

	//mSocketSendBA.m_startTest = true;
}

// ѹ������ÿһ����
void ClientBuffer::CompressAndEncryptEveryOne()
{
	uint32 origMsgLen = 0;    // ԭʼ����Ϣ���ȣ������ж�ͷ���Ƿ����ѹ����־
	uint32 compressMsgLen = 0;
#if MSG_ENCRIPT
	uint cryptLen = 0;
#endif
#if MSG_COMPRESS && !MSG_ENCRIPT
	bool bHeaderChange = false; // ��Ϣ������ǰ����ĸ��ֽ�����Ϣ�ĳ����Ƿ���Ҫ�������
#endif
	while (mSocketSendBA->getBytesAvailable() > 0)
	{
#if MSG_COMPRESS && !MSG_ENCRIPT
		bHeaderChange = false;
#endif

		mSocketSendBA->readUnsignedInt32(origMsgLen);    // ��ȡһ����Ϣ��ͷ

#if MSG_COMPRESS
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
		// ֻ������Ϣ body
		//#if MSG_ENCRIPT
		//                mSocketSendBA.position -= compressMsgLen;      // �ƶ�����ָ��λ��
		//                cryptLen = mSocketSendBA.encrypt(m_cryptKeyArr[(int)m_cryptAlgorithm], compressMsgLen, m_cryptAlgorithm);
		//                if (compressMsgLen != cryptLen)
		//                {
		//                    bHeaderChange = true;
		//                }
		//                compressMsgLen = cryptLen;
		//#endif

		// �������ϵͳ�����ֽڣ����ȿ��ܻ��� 8 �ֽڵ�֤�鱶�������Ҫ�ȼ�����ɺ���д�볤��
#if MSG_COMPRESS && !MSG_ENCRIPT
		if (origMsgLen > DataCV::PACKET_ZIP_MIN)    // ���ԭʼ������Ҫѹ��
		{
			bHeaderChange = true;
			origMsgLen = compressMsgLen;                // ѹ����ĳ���
			origMsgLen |= DataCV::PACKET_ZIP;            // ���
		}
		//#endif
		//#if !MSG_ENCRIPT
		if (bHeaderChange)
		{
			mSocketSendBA->position -= (compressMsgLen + 4);        // �ƶ���ͷ��λ��
			mSocketSendBA->writeUnsignedInt32(origMsgLen, false);     // д��ѹ�����߼��ܺ����Ϣ����
			mSocketSendBA->incPosDelta(compressMsgLen);              // �ƶ�����һ��λ��
		}
#endif

		// ������Ϣѹ���󣬰��� 4 ���ֽ�ͷ�ĳ��ȣ�Ȼ����������
#if MSG_ENCRIPT
		cryptLen = ((compressMsgLen + 4 + 7) / 8) * 8 - 4;      // ������ܺ󣬲����� 4 ��ͷ���ȵ� body ����
		if (origMsgLen > MsgCV::PACKET_ZIP_MIN)    // ���ԭʼ������Ҫѹ��
		{
			origMsgLen = cryptLen;                // ѹ����ĳ���
			origMsgLen |= MsgCV::PACKET_ZIP;            // ���
		}
		else
		{
			origMsgLen = cryptLen;                // ѹ����ĳ���
		}

		mSocketSendBA->decPosDelta((compressMsgLen + 4));        // �ƶ���ͷ��λ��
		mSocketSendBA->writeUnsignedInt32(origMsgLen, false);     // д��ѹ�����߼��ܺ����Ϣ����

		mSocketSendBA.decPosDelta(4);      // �ƶ���ͷ��
		mSocketSendBA.encrypt(mCryptContext, 0);  // ����
#endif
	}

	// ������Ϣѹ���󣬰��� 4 ���ֽ�ͷ�ĳ��ȣ�Ȼ����������
	//#if MSG_ENCRIPT
	//mSocketSendBA.position = 0;      // �ƶ���ͷ��
	//mSocketSendBA.encrypt(m_cryptKeyArr[(int)m_cryptAlgorithm], 0, m_cryptAlgorithm);
	//#endif
}

// ѹ��������Ϊһ����
void ClientBuffer::CompressAndEncryptAllInOne()
{
#if MSG_COMPRESS
	uint origMsgLen = mSocketSendBA.length;       // ԭʼ����Ϣ���ȣ������ж�ͷ���Ƿ����ѹ����־
	uint compressMsgLen = 0;
	if (origMsgLen > MsgCV.PACKET_ZIP_MIN)
	{
		compressMsgLen = mSocketSendBA.compress();
	}
#endif

#if MSG_ENCRIPT
	else
	{
		compressMsgLen = origMsgLen;
		mSocketSendBA.position += origMsgLen;
	}

	mSocketSendBA.position -= compressMsgLen;
	compressMsgLen = mSocketSendBA.encrypt(mCryptContext, 0);
#endif

#if MSG_COMPRESS || MSG_ENCRIPT             // ���ѹ�����߼��ܣ���Ҫ�ٴ����ѹ�����߼��ܺ��ͷ����
	if (origMsgLen > MsgCV.PACKET_ZIP_MIN)    // ���ԭʼ������Ҫѹ��
	{
		origMsgLen = compressMsgLen;
		origMsgLen |= MsgCV.PACKET_ZIP;            // ���
	}
	else
	{
		origMsgLen = compressMsgLen;
	}

	mSocketSendBA.position = 0;
	mSocketSendBA.insertUnsignedInt32(origMsgLen);            // д��ѹ�����߼��ܺ����Ϣ����
#endif
}

// ��Ϣ��ʽ
// |------------- ���ܵ�������Ϣ  -------------------------------------|
// |----4 Header----|-ѹ���� body----|----4 Header----|-ѹ���� body----|
// |                |                |                |                |
void ClientBuffer::UnCompressAndDecryptEveryOne()
{
#if MSG_ENCRIPT
	mRawBuffer.msgBodyBA.decrypt(mCryptContext, 0);
#endif
	//#if MSG_COMPRESS
	//mRawBuffer.headerBA.setPos(0); // ���ͷĿǰû���ã��ǿͻ����Լ���ӵģ�����������һ����������Ϊ��һ�������İ�
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
		mRawBuffer->getMsgBodyBA()->readUnsignedInt32(msglen);    // ��ȡһ����Ϣ��ͷ
		if (msglen == 0)     // ����� 0 ����˵����������ڼ��ܲ��������
		{
			break;
		}
#if MSG_COMPRESS
		if ((msglen & MsgCV::PACKET_ZIP) > 0)
		{
			msglen &= (~MsgCV.PACKET_ZIP);         // ȥ��ѹ����־λ
			Ctx.m_instance.m_logSys.log(string.Format("��Ϣ��Ҫ��ѹ������Ϣδ��ѹ���ȡ�{0}", msglen));
			msglen = mRawBuffer->getMsgBodyBA->uncompress(msglen);
			Ctx.m_instance.m_logSys.log(string.Format("��Ϣ��Ҫ��ѹ������Ϣ��ѹ�󳤶ȡ�{0}", msglen));
		}
		else
#endif
		{
			GLogSys->log(UtilStr::Format("��Ϣ����Ҫ��ѹ������Ϣԭʼ���ȡ�{0}", msglen));
			mRawBuffer->getMsgBodyBA()->incPosDelta(msglen);
		}

		mUnCompressHeaderBA->clear();
		mUnCompressHeaderBA->writeUnsignedInt32(msglen);        // д���ѹ�����Ϣ�ĳ��ȣ���Ҫд�� msglen �����ѹ�����ټ��ܣ����ܺ��ٽ�ѹ��ĳ��Ȳ��������ĳ���
		mUnCompressHeaderBA->setPos(0);

#if NET_MULTHREAD
		using (MLock mlock = new MLock(mReadMutex))
#endif
		{
			mMsgBuffer->getCircularBuffer()->pushBackBA(mUnCompressHeaderBA);             // ������Ϣ��С�ֶ�
			mMsgBuffer->getCircularBuffer()->pushBackArr(mRawBuffer->getMsgBodyBA()->getDynBuffer()->getBuffer(), mRawBuffer->getMsgBodyBA()->getPos() - msglen, msglen);      // ������Ϣ��С�ֶ�
		}

		GLogSys->log(UtilStr::Format("��ѹ���ܺ���Ϣ��ʼ���� {0}, ��Ϣ���ȡ�{1}, ��Ϣ position λ�� {2}, ��Ϣ size {3}", mRawBuffer->getMsgBodyBA()->getPos() - msglen, msglen, mRawBuffer->getMsgBodyBA()->getPos(), mRawBuffer->getMsgBodyBA()->getLength()));
		GNetDispList->addOneRevMsg();

		// Test ��ȡ��Ϣͷ
		// ByteBuffer buff = getMsg();
		// stNullUserCmd cmd = new stNullUserCmd();
		// cmd.derialize(buff);
		// Ctx.m_instance.m_logSys.log(string.Format("���Դ�ӡ��Ϣ: byCmd = {0}, byParam = {1}", cmd.byCmd, cmd.byParam));
	}
}

void ClientBuffer::UnCompressAndDecryptAllInOne()
{
#if MSG_ENCRIPT
	mRawBuffer.msgBodyBA.decrypt(mCryptContext, 0);
#endif
#if MSG_COMPRESS
	mRawBuffer.headerBA.setPos(0);
	uint msglen = 0;
	mRawBuffer.headerBA.readUnsignedInt32(ref msglen);
	if ((msglen & MsgCV.PACKET_ZIP) > 0)
	{
		mRawBuffer.msgBodyBA.uncompress();
	}
#endif

#if !MSG_COMPRESS && !MSG_ENCRIPT
	mUnCompressHeaderBA->clear();
	mUnCompressHeaderBA->writeUnsignedInt32(mRawBuffer->getMsgBodyBA()->getLength());
	mUnCompressHeaderBA->setPos(0);
#endif
#if NET_MULTHREAD
	using (MLock mlock = new MLock(mReadMutex))
#endif
	{
#if !MSG_COMPRESS && !MSG_ENCRIPT
		mMsgBuffer->getCircularBuffer()->pushBackBA(mUnCompressHeaderBA);             // ������Ϣ��С�ֶ�
#endif
		mMsgBuffer->getCircularBuffer()->pushBackBA(mRawBuffer->getMsgBodyBA());      // ������Ϣ��С�ֶ�
	}
}