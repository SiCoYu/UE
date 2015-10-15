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
	m_rawBuffer = new MsgBuffer();
	m_msgBuffer = new MsgBuffer();
	//m_sendTmpBA = new ByteBuffer();
	m_sendTmpBuffer = new MsgBuffer();
	m_socketSendBA = new ByteBuffer();
	//m_socketSendBA.m_id = 1000;

	//m_dynBuff = new DynamicBuffer<byte>(8096);
	m_unCompressHeaderBA = new ByteBuffer();
	m_sendData = new ByteBuffer();
	m_tmpData = new ByteBuffer(4);
	m_tmp1fData = new ByteBuffer(4);

	m_readMutex = new MMutex();
	m_writeMutex = new MMutex();

#if MSG_ENCRIPT
	m_cryptContext = new CryptContext();
#endif
}

ClientBuffer::~ClientBuffer()
{
	delete m_rawBuffer;
	delete m_msgBuffer;
	delete m_sendTmpBuffer;

	delete m_socketSendBA;
	delete m_unCompressHeaderBA;
	delete m_sendData;
	delete m_tmpData;

	delete m_readMutex;
	delete m_writeMutex;

#if MSG_ENCRIPT
	delete m_cryptContext;
#endif
}

DynBuffer* ClientBuffer::getDynBuff()
{
	return m_dynBuff;
}


MsgBuffer* ClientBuffer::getSendTmpBuffer()
{
	return m_sendTmpBuffer;
}

ByteBuffer* ClientBuffer::getSendBuffer()
{
	return m_socketSendBA;
}

ByteBuffer* ClientBuffer::getSendData()
{
	return m_sendData;
}

#if MSG_ENCRIPT
public void ClientBuffer::setCryptKey(byte[] encrypt)
{
	//m_cryptContext.cryptAlgorithm = CryptAlgorithm.DES;
	m_cryptContext.m_cryptKey = encrypt;
	Dec.DES_set_key_unchecked(m_cryptContext.m_cryptKey, m_cryptContext.m_cryptKeyArr[(int)CryptAlgorithm.DES] as DES_key_schedule);
}

public void ClientBuffer::checkDES()
{
	if (m_cryptContext.m_cryptKey != null && m_cryptContext.m_cryptAlgorithm != CryptAlgorithm.DES)
	{
		m_cryptContext.m_cryptAlgorithm = CryptAlgorithm.DES;
	}
}
#endif

MsgBuffer* ClientBuffer::getRawBuffer()
{
	return m_rawBuffer;
}

void ClientBuffer::SetRevBufferSize(int32 size)
{
	m_dynBuff = new DynBuffer<char>(size);
}

void ClientBuffer::moveDyn2Raw()
{
	g_pLogSys->log(UtilStr::Format("�ƶ���̬������Ϣ���ݵ�ԭʼ���ݶ��У���Ϣ���ȡ�{0}", m_dynBuff->getSize()));
	UtilMsg::formatBytes2Array(m_dynBuff->getBuff(), m_dynBuff->getSize());

#if MSG_ENCRIPT
	checkDES();
#endif
	// ���յ�һ��socket���ݣ��ͱ���Ϊ��һ�����ݰ�������ط����ܻ������⣬����������ô���͵ģ�ֻ����ô�����Լ�д����ĳ���
	m_tmp1fData->clear();
	m_tmp1fData->writeUnsignedInt32(m_dynBuff->getSize());      // ��䳤��
	m_rawBuffer->getCircularBuffer()->pushBackBA(m_tmp1fData);
	// д���������
	m_rawBuffer->getCircularBuffer()->pushBackArr(m_dynBuff->getBuff(), 0, m_dynBuff->getSize());
}

void ClientBuffer::moveRaw2Msg()
{
	while (m_rawBuffer->popFront())  // ���������
	{
		//UnCompressAndDecryptAllInOne();
		UnCompressAndDecryptEveryOne();
	}
}

void ClientBuffer::send(bool bnet)
{
	m_tmpData->clear();
	m_tmpData->writeUnsignedInt32(m_sendData->getLength());      // ��䳤��

	if (bnet)       // �� socket ���ͳ�ȥ
	{
#if NET_MULTHREAD
		using (MLock mlock = new MLock(m_writeMutex))
#endif
		{
			//m_sendTmpBA.writeUnsignedInt(m_sendData.length);                            // д��ͷ������
			//m_sendTmpBA.writeBytes(m_sendData.dynBuff.buff, 0, m_sendData.length);      // д������

			m_sendTmpBuffer->getCircularBuffer()->pushBackBA(m_tmpData);
			m_sendTmpBuffer->getCircularBuffer()->pushBackBA(m_sendData);
		}
	}
	else        // ֱ�ӷ��������Ϣ������
	{
#if NET_MULTHREAD

#endif
		{
			//m_tmpData.clear();
			//m_tmpData.writeUnsignedInt(m_sendData.length);      // ��䳤��

			m_msgBuffer->getCircularBuffer()->pushBackBA(m_tmpData);              // ������Ϣ��С�ֶ�
			m_msgBuffer->getCircularBuffer()->pushBackBA(m_sendData);             // ������Ϣ��С�ֶ�
		}
	}
}

ByteBuffer* ClientBuffer::getMsg()
{
	MLock mlock(m_readMutex);
	{
		if (m_msgBuffer->popFront())
		{
			return m_msgBuffer->getMsgBodyBA();
		}
	}

	return nullptr;
}

// ��ȡ���ݣ�Ȼ��ѹ������
void ClientBuffer::getSocketSendData()
{
	//m_socketSendBA.m_startTest = false;

	m_socketSendBA->clear();

	// ��ȡ�����ݣ��ͽ���
#if NET_MULTHREAD
	using (MLock mlock = new MLock(m_writeMutex))
#endif
	{
		//m_socketSendBA.writeBytes(m_sendTmpBA.dynBuff.buff, 0, (uint)m_sendTmpBA.length);
		//m_sendTmpBA.clear();
		// һ��ȫ��ȡ�������ͳ�ȥ
		//m_socketSendBA.writeBytes(m_sendTmpBuffer.circuleBuffer.buff, 0, (uint)m_sendTmpBuffer.circuleBuffer.size);
		//m_sendTmpBuffer.circuleBuffer.clear();
		// һ�ν�����ȡһ����Ϣ���ͳ�ȥ����Ϊÿһ����Ϣ�ĳ���Ҫ��д���ܲ�λ��ĳ���
		if (m_sendTmpBuffer->popFront())     // ����һ����Ϣ�����ֻ��һ����Ϣ���ڲ������ñ���
		{
			m_socketSendBA->writeBytes(m_sendTmpBuffer->getHeaderBA()->getDynBuff()->getBuff(), 0, m_sendTmpBuffer->getHeaderBA()->getLength());       // д��ͷ
			m_socketSendBA->writeBytes(m_sendTmpBuffer->getMsgBodyBA()->getDynBuff()->getBuff(), 0, m_sendTmpBuffer->getMsgBodyBA()->getLength());             // д����Ϣ��
		}
	}

#if MSG_COMPRESS || MSG_ENCRIPT
	m_socketSendBA.setPos(0);
	CompressAndEncryptEveryOne();
	// CompressAndEncryptAllInOne();
#endif
	m_socketSendBA->setPos(0);        // ����ָ�� pos

	//m_socketSendBA.m_startTest = true;
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
	while (m_socketSendBA->getBytesAvailable() > 0)
	{
#if MSG_COMPRESS && !MSG_ENCRIPT
		bHeaderChange = false;
#endif

		m_socketSendBA->readUnsignedInt32(origMsgLen);    // ��ȡһ����Ϣ��ͷ

#if MSG_COMPRESS
		if (origMsgLen > MsgCV::PACKET_ZIP_MIN)
		{
			compressMsgLen = m_socketSendBA->compress(origMsgLen);
		}
		else
		{
			m_socketSendBA->incPosDelta(origMsgLen);
			compressMsgLen = origMsgLen;
		}
#endif
		// ֻ������Ϣ body
		//#if MSG_ENCRIPT
		//                m_socketSendBA.position -= compressMsgLen;      // �ƶ�����ָ��λ��
		//                cryptLen = m_socketSendBA.encrypt(m_cryptKeyArr[(int)m_cryptAlgorithm], compressMsgLen, m_cryptAlgorithm);
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
			m_socketSendBA->position -= (compressMsgLen + 4);        // �ƶ���ͷ��λ��
			m_socketSendBA->writeUnsignedInt32(origMsgLen, false);     // д��ѹ�����߼��ܺ����Ϣ����
			m_socketSendBA->incPosDelta(compressMsgLen);              // �ƶ�����һ��λ��
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

		m_socketSendBA->decPosDelta((compressMsgLen + 4));        // �ƶ���ͷ��λ��
		m_socketSendBA->writeUnsignedInt32(origMsgLen, false);     // д��ѹ�����߼��ܺ����Ϣ����

		m_socketSendBA.decPosDelta(4);      // �ƶ���ͷ��
		m_socketSendBA.encrypt(m_cryptContext, 0);  // ����
#endif
	}

	// ������Ϣѹ���󣬰��� 4 ���ֽ�ͷ�ĳ��ȣ�Ȼ����������
	//#if MSG_ENCRIPT
	//m_socketSendBA.position = 0;      // �ƶ���ͷ��
	//m_socketSendBA.encrypt(m_cryptKeyArr[(int)m_cryptAlgorithm], 0, m_cryptAlgorithm);
	//#endif
}

// ѹ��������Ϊһ����
void ClientBuffer::CompressAndEncryptAllInOne()
{
#if MSG_COMPRESS
	uint origMsgLen = m_socketSendBA.length;       // ԭʼ����Ϣ���ȣ������ж�ͷ���Ƿ����ѹ����־
	uint compressMsgLen = 0;
	if (origMsgLen > MsgCV.PACKET_ZIP_MIN)
	{
		compressMsgLen = m_socketSendBA.compress();
	}
#endif

#if MSG_ENCRIPT
	else
	{
		compressMsgLen = origMsgLen;
		m_socketSendBA.position += origMsgLen;
	}

	m_socketSendBA.position -= compressMsgLen;
	compressMsgLen = m_socketSendBA.encrypt(m_cryptContext, 0);
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

	m_socketSendBA.position = 0;
	m_socketSendBA.insertUnsignedInt32(origMsgLen);            // д��ѹ�����߼��ܺ����Ϣ����
#endif
}

// ��Ϣ��ʽ
// |------------- ���ܵ�������Ϣ  -------------------------------------|
// |----4 Header----|-ѹ���� body----|----4 Header----|-ѹ���� body----|
// |                |                |                |                |
void ClientBuffer::UnCompressAndDecryptEveryOne()
{
#if MSG_ENCRIPT
	m_rawBuffer.msgBodyBA.decrypt(m_cryptContext, 0);
#endif
	//#if MSG_COMPRESS
	//m_rawBuffer.headerBA.setPos(0); // ���ͷĿǰû���ã��ǿͻ����Լ���ӵģ�����������һ����������Ϊ��һ�������İ�
	//m_rawBuffer.msgBodyBA.setPos(0);
	//uint msglen = m_rawBuffer.headerBA.readUnsignedInt();
	//if ((msglen & DataCV.PACKET_ZIP) > 0)
	//{
	//    m_rawBuffer.msgBodyBA.uncompress();
	//}
	//#endif

	m_rawBuffer->getMsgBodyBA()->setPos(0);

	uint32 msglen = 0;
	while (m_rawBuffer->getMsgBodyBA()->getBytesAvailable() >= 4)
	{
		m_rawBuffer->getMsgBodyBA()->readUnsignedInt32(msglen);    // ��ȡһ����Ϣ��ͷ
		if (msglen == 0)     // ����� 0 ����˵����������ڼ��ܲ��������
		{
			break;
		}
#if MSG_COMPRESS
		if ((msglen & MsgCV::PACKET_ZIP) > 0)
		{
			msglen &= (~MsgCV.PACKET_ZIP);         // ȥ��ѹ����־λ
			Ctx.m_instance.m_logSys.log(string.Format("��Ϣ��Ҫ��ѹ������Ϣδ��ѹ���ȡ�{0}", msglen));
			msglen = m_rawBuffer->getMsgBodyBA->uncompress(msglen);
			Ctx.m_instance.m_logSys.log(string.Format("��Ϣ��Ҫ��ѹ������Ϣ��ѹ�󳤶ȡ�{0}", msglen));
		}
		else
#endif
		{
			g_pLogSys->log(UtilStr::Format("��Ϣ����Ҫ��ѹ������Ϣԭʼ���ȡ�{0}", msglen));
			m_rawBuffer->getMsgBodyBA()->incPosDelta(msglen);
		}

		m_unCompressHeaderBA->clear();
		m_unCompressHeaderBA->writeUnsignedInt32(msglen);        // д���ѹ�����Ϣ�ĳ��ȣ���Ҫд�� msglen �����ѹ�����ټ��ܣ����ܺ��ٽ�ѹ��ĳ��Ȳ��������ĳ���
		m_unCompressHeaderBA->setPos(0);

#if NET_MULTHREAD
		using (MLock mlock = new MLock(m_readMutex))
#endif
		{
			m_msgBuffer->getCircularBuffer()->pushBackBA(m_unCompressHeaderBA);             // ������Ϣ��С�ֶ�
			m_msgBuffer->getCircularBuffer()->pushBackArr(m_rawBuffer->getMsgBodyBA()->getDynBuff()->getBuff(), m_rawBuffer->getMsgBodyBA()->getPos() - msglen, msglen);      // ������Ϣ��С�ֶ�
		}

		g_pLogSys->log(UtilStr::Format("��ѹ���ܺ���Ϣ��ʼ���� {0}, ��Ϣ���ȡ�{1}, ��Ϣ position λ�� {2}, ��Ϣ size {3}", m_rawBuffer->getMsgBodyBA()->getPos() - msglen, msglen, m_rawBuffer->getMsgBodyBA()->getPos(), m_rawBuffer->getMsgBodyBA()->getLength()));
		g_pNetDispList->addOneRevMsg();

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
	m_rawBuffer.msgBodyBA.decrypt(m_cryptContext, 0);
#endif
#if MSG_COMPRESS
	m_rawBuffer.headerBA.setPos(0);
	uint msglen = 0;
	m_rawBuffer.headerBA.readUnsignedInt32(ref msglen);
	if ((msglen & MsgCV.PACKET_ZIP) > 0)
	{
		m_rawBuffer.msgBodyBA.uncompress();
	}
#endif

#if !MSG_COMPRESS && !MSG_ENCRIPT
	m_unCompressHeaderBA->clear();
	m_unCompressHeaderBA->writeUnsignedInt32(m_rawBuffer->getMsgBodyBA()->getLength());
	m_unCompressHeaderBA->setPos(0);
#endif
#if NET_MULTHREAD
	using (MLock mlock = new MLock(m_readMutex))
#endif
	{
#if !MSG_COMPRESS && !MSG_ENCRIPT
		m_msgBuffer->getCircularBuffer()->pushBackBA(m_unCompressHeaderBA);             // ������Ϣ��С�ֶ�
#endif
		m_msgBuffer->getCircularBuffer()->pushBackBA(m_rawBuffer->getMsgBodyBA());      // ������Ϣ��С�ֶ�
	}
}