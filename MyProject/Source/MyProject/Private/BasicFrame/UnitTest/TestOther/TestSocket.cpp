#include "MyProject.h"
#include "TestSocket.h"

#ifdef USE_EXTERN_THREAD

TestSocket::TestSocket()
{
	SocketHandler aaa(NULL);
	mTcpSocket = new TcpSocket(aaa);
}

#endif	// USE_EXTERN_THREAD
