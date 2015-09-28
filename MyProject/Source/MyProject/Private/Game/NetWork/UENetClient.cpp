#include "MyProject.h"
#include "UENetClient.h"
#include "NetClientBuffer.h"

UENetClient::UENetClient()
{
	m_pNetClientBuffer = new NetClientBuffer();
}

UENetClient::~UENetClient()
{
	delete m_pNetClientBuffer;
}

void UENetClient::OnConnect()
{
	
}

void UENetClient::OnConnectFailed()
{
	
}

void UENetClient::OnDelete()
{

}

void UENetClient::OnRawData(const char *buf, size_t len)
{

}

NetClientBuffer* UENetClient::getNetClientBuffer()
{
	return m_pNetClientBuffer;
}

void UENetClient::sendMsg()
{
	m_pNetClientBuffer->sendMsg();
}