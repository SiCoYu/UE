#include "MyProject.h"
#include "TestSocket.h"

TestSocket::TestSocket()
{
	SocketHandler aaa(NULL);
	mTcpSocket = new TcpSocket(aaa);
}
