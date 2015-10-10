#include "MyProject.h"
#include "MsgBuffer.h"
#include "MCircularBuffer.h"
#include "ByteBuffer.h"
#include "MsgCV.h"

public MsgBuffer(uint32 initCapacity, uint32 maxCapacity)
{
	m_circularBuffer = new MCircularBuffer(initCapacity, maxCapacity);
	m_headerBA = new ByteBuffer();
	m_msgBodyBA = new ByteBuffer();
}

MsgBuffer::~MsgBuffer()
{
	delete m_circularBuffer;
	delete m_headerBA;
	delete m_msgBodyBA;
}

ByteBuffer* MsgBuffer::getHeaderBA()
{
	return m_headerBA;
}

ByteBuffer* MsgBuffer::getMsgBodyBA()
{
	return m_msgBodyBA;
}

MCircularBuffer* MsgBuffer::getCircularBuffer()
{
	return m_circularBuffer;
}

bool MsgBuffer::checkHasMsg()
{
	m_circularBuffer->frontBA(m_headerBA, MsgCV.HEADER_SIZE);  // �����ݶ�ȡ�� m_headerBA
	uint msglen = 0;
	m_headerBA->readUnsignedInt32(msglen);
#if MSG_COMPRESS
	if ((msglen & MsgCV.PACKET_ZIP) > 0)         // �����ѹ����־
	{
		msglen &= (~MsgCV.PACKET_ZIP);         // ȥ��ѹ����־λ
	}
#endif
	if (msglen <= m_circularBuffer->getSize() - MsgCV.HEADER_SIZE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
* @brief ��ȡǰ��ĵ�һ����������Ϣ���ݿ�
*/
bool MsgBuffer::popFront()
{
	bool ret = false;
	if (m_circularBuffer->getSize() > MsgCV.HEADER_SIZE)         // ����Ҫ�� DataCV.HEADER_SIZE ��С�� 1 ����������� DataCV.HEADER_SIZE ����ֻ��˵��ֻ�д�С�ֶΣ�û������
	{
		m_circularBuffer->frontBA(m_headerBA, MsgCV.HEADER_SIZE);  // �������������Ϣ�ĳ��ȣ����ǲ���ȥ����Ϣͷ��
		uint msglen = 0;
		m_headerBA->readUnsignedInt32(ref msglen);
#if MSG_COMPRESS
		if ((msglen & MsgCV.PACKET_ZIP) > 0)         // �����ѹ����־
		{
			msglen &= (~MsgCV.PACKET_ZIP);         // ȥ��ѹ����־λ
		}
#endif

		if (msglen <= m_circularBuffer->getSize() - MsgCV.HEADER_SIZE)
		{
			m_circularBuffer->popFrontLen(MsgCV.HEADER_SIZE);
			m_circularBuffer->popFrontBA(m_msgBodyBA, msglen);
			ret = true;
		}
	}

	if (m_circularBuffer->empty())     // ����Ѿ���գ���ֱ������
	{
		m_circularBuffer->clear();    // ��дָ���ͷ��ʼ����ʽд����Ҫд��������
	}

	return ret;
}