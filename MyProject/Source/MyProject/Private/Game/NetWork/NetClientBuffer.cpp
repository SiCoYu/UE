#include "MyProject.h"
#include "NetClientBuffer.h"
#include "MsgBuffer.h"
#include "DynBuffer.h"
#include "ByteBuffer.h"
#include "MCircularBuffer.h"

NetClientBuffer::NetClientBuffer()
{
	m_recvSocketBuffer = new MsgBuffer();
	m_recvClientBuffer = new MsgBuffer();
	m_recvSocketDynBuffer = new DynBuffer();

	m_sendClientBuffer = new MsgBuffer();
	m_sendSocketBuffer = new MsgBuffer();
	m_sendClientBA = new ByteBuffer();

	m_unCompressHeaderBA = new ByteBuffer();
	m_tmpData = new ByteBuffer();
}

NetClientBuffer::~NetClientBuffer()
{
	delete m_recvSocketBuffer;
	delete m_recvClientBuffer;
	delete m_recvSocketDynBuffer;

	delete m_sendClientBuffer;
	delete m_sendSocketBuffer;
	delete m_sendClientBA;

	delete m_unCompressHeaderBA;
	delete m_tmpData;
}

void NetClientBuffer::moveRecvSocketDyn2RecvSocket()
{
	m_recvSocketBuffer->m_pMCircularBuffer->pushBack(m_recvSocketDynBuffer->m_storage, 0, m_recvSocketDynBuffer->size());
}

// 有可能一个数据包有多个消息，这个地方没有处理，如果有多个消息，需要处理，否则会丢失消息
void NetClientBuffer::moveRecvSocket2RecvClient()
{
	while (m_recvSocketBuffer->checkHasMsg())  // 如果有数据
	{
		m_recvSocketBuffer->moveOutOneMsg();
		//m_recvSocketBuffer->m_pMsgBA->uncompress();
		m_unCompressHeaderBA->clear();
		m_unCompressHeaderBA->writeUnsignedInt32(m_recvSocketBuffer->m_pMsgBA->size());
		m_unCompressHeaderBA->rpos(0);
		m_recvClientBuffer->m_pMCircularBuffer->pushBack(m_unCompressHeaderBA->contents(), 0, MSGHEADERSIZE);             // 保存消息大小字段
		m_recvClientBuffer->m_pMCircularBuffer->pushBack(m_recvSocketBuffer->m_pMsgBA->contents(), 0, m_recvSocketBuffer->m_pMsgBA->size());      // 保存消息大小字段
	}
}

ByteArray NetClientBuffer::getMsg()
{
	if (m_msgBuffer->checkHasMsg())
	{
		return m_msgBuffer->m_pMsgBA;
	}

	return nullptr;
}

void NetClientBuffer::sendMsg()
{
	m_tmpData->clear();
	m_tmpData->writeUnsignedInt32(m_sendClientBA->size());      // 填充长度
	m_sendClientBuffer->pushBack(m_tmpData->contents(), 0, m_tmpData->size());
	m_sendClientBuffer->pushBack(m_sendClientBA->contents(), 0, m_sendClientBA->size());
}

// 获取数据，然后压缩加密
void NetClientBuffer::moveSendClient2SendSocket()
{
	m_sendSocketBuffer->clear();           // 清理之前的缓冲区
	m_sendSocketBuffer->pushBack(m_sendClientBuffer->contents(), 0, m_sendClientBuffer->size());
	m_sendClientBuffer->clear();
}