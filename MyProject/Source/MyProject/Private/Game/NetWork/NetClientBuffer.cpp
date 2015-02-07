#include "MyProject.h"
#include "NetClientBuffer.h"
#include "MsgBuffer.h"
#include "DynBuffer.h"
#include "ByteBuffer.h"

NetClientBuffer::NetClientBuffer()
{
	m_recvRawBuffer;
	m_recvMsgBuffer;
	m_sendRawBuffer;
	m_sendMsgBuffer;

	m_dynBuff;
	m_unCompressHeaderBA;
	m_sendData;
	m_tmpData;
}

NetClientBuffer::~NetClientBuffer()
{

}