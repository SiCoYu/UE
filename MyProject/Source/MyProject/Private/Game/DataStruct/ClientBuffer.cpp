#include "MyProject.h"
#include "NetClientBuffer.h"
#include "MsgBuffer.h"
#include "DynBuffer.h"
#include "ByteBuffer.h"
#include "MCircularBuffer.h"
#include "BufferDefaultValue.h"

#ifdef USE_EXTERN_THREAD

	#include "Windows/AllowWindowsPlatformTypes.h"

	#include "Sockets/Mutex.h"

	#include "Windows/HideWindowsPlatformTypes.h"

#endif

ClientBuffer::ClientBuffer()
{
	m_recvSocketBuffer = new MsgBuffer();
	m_recvClientBuffer = new MsgBuffer();
	m_recvSocketDynBuffer = new DynBuffer(INITCAPACITY);

	m_sendClientBuffer = new MCircularBuffer(INITCAPACITY);
	m_sendSocketBuffer = new MCircularBuffer(INITCAPACITY);
	m_sendClientBA = new ByteBuffer(INITCAPACITY);

	m_unCompressHeaderBA = new ByteBuffer(MSGHEADERSIZE);
	m_pHeaderBA = new ByteBuffer(MSGHEADERSIZE);
	m_pMsgBA = new DynBuffer(INITCAPACITY);

#ifdef USE_EXTERN_THREAD
	m_pMutex = new Mutex();
#else
	m_pMutex = new FCriticalSection();
#endif
}

ClientBuffer::~ClientBuffer()
{
	delete m_recvSocketBuffer;
	delete m_recvClientBuffer;
	delete m_recvSocketDynBuffer;

	delete m_sendClientBuffer;
	delete m_sendSocketBuffer;
	delete m_sendClientBA;

	delete m_unCompressHeaderBA;

#ifdef USE_EXTERN_THREAD
	delete m_pMutex;
#else
	delete m_pMutex;
#endif
}

void ClientBuffer::moveRecvSocketDyn2RecvSocket()
{
	m_recvSocketBuffer->m_pMCircularBuffer->pushBack(m_recvSocketDynBuffer->m_storage, 0, m_recvSocketDynBuffer->size());
}

// 有可能一个数据包有多个消息，这个地方没有处理，如果有多个消息，需要处理，否则会丢失消息
void ClientBuffer::moveRecvSocket2RecvClient()
{
	while (m_recvSocketBuffer->checkHasMsg())  // 如果有数据
	{
		m_recvSocketBuffer->moveOutOneMsg();
		//m_recvSocketBuffer->m_pMsgBA->uncompress();
		m_unCompressHeaderBA->clear();
		m_unCompressHeaderBA->writeUnsignedInt32(m_recvSocketBuffer->m_pMsgBA->size());
		m_unCompressHeaderBA->pos(0);
		m_recvClientBuffer->m_pMCircularBuffer->pushBack((char*)m_unCompressHeaderBA->getStorage(), 0, MSGHEADERSIZE);             // 保存消息大小字段
		m_recvClientBuffer->m_pMCircularBuffer->pushBack((char*)m_recvSocketBuffer->m_pMsgBA->getStorage(), 0, m_recvSocketBuffer->m_pMsgBA->size());      // 保存消息大小字段
	}
}

ByteBuffer* ClientBuffer::getMsg()
{
	if (m_recvClientBuffer->checkHasMsg())
	{
		return m_recvClientBuffer->m_pMsgBA;
	}

	return nullptr;
}

void ClientBuffer::sendMsg()
{
	m_pHeaderBA->clear();
	m_pHeaderBA->writeUnsignedInt32(m_sendClientBA->size());      // 填充长度

#ifdef USE_EXTERN_THREAD
	m_pMutex->Lock();
#else
	//FScopeLock Lock(&m_pMutex);
	m_pMutex->Lock();
#endif

	m_sendClientBuffer->pushBack((char*)m_pHeaderBA->getStorage(), 0, m_pHeaderBA->size());
	m_sendClientBuffer->pushBack((char*)m_sendClientBA->getStorage(), 0, m_sendClientBA->size());

#ifdef USE_EXTERN_THREAD
	m_pMutex->Unlock();
#endif
}

// 获取数据，然后压缩加密
void ClientBuffer::moveSendClient2SendSocket()
{
	m_sendSocketBuffer->clear(); // 清理，这样环形缓冲区又可以从 0 索引开始了

#ifdef USE_EXTERN_THREAD
	m_pMutex->Lock();
#else
	m_pMutex->Lock();
#endif

	m_pMsgBA->setSize(m_sendClientBuffer->size());
	m_sendClientBuffer->popFront(m_pMsgBA->getStorage(), 0, m_sendClientBuffer->size());

#ifdef USE_EXTERN_THREAD
	m_pMutex->Unlock();
#else
	m_pMutex->Unlock();
#endif

	m_sendSocketBuffer->pushBack(m_pMsgBA->getStorage(), 0, m_pMsgBA->size());
	m_sendClientBuffer->clear(); // 清理，这样环形缓冲区又可以从 0 索引开始了
}