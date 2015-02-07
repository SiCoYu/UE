#include "MyProject.h"
#include "MsgBuffer.h"
#include "MCircularBuffer.h"
#include "ByteBuffer.h"

MsgBuffer::MsgBuffer()
{

}

MsgBuffer::~MsgBuffer()
{

}

bool MsgBuffer::checkHasMsg()
{
	if (m_pMCircularBuffer->size() <= MSGHEADERSIZE)
	{
		return false;
	}

	m_pHeaderBA->clear();
	m_pMCircularBuffer->front(m_pHeaderBA->contents(), 0, MSGHEADERSIZE);

	m_pHeaderBA->readUnsignedInt32(m_msgLen);
	if (m_msgLen + MSGHEADERSIZE <= m_pMCircularBuffer->size())
	{
		return true;
	}

	return false;
}

// 移出一个消息
void MsgBuffer::moveOutOneMsg()
{
	m_pMCircularBuffer->popFrontLenNoData(MSGHEADERSIZE);

	if (m_pMsgBA->size() < m_msgLen)
	{
		m_pMsgBA->resize(m_msgLen);
	}
	m_pMsgBA->clear();

	m_pMCircularBuffer->popFront(m_pMsgBA->contents(), 0, m_msgLen);
}