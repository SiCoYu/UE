#include "MyProject.h"
#include "TestSocket.h"

TestSocket::TestSocket()
{
	SocketHandler aaa(NULL);
	m_tcpSocket = new TcpSocket(aaa);
}
