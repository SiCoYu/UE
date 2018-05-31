#include "MyProject.h"
#include "TestSocket.h"

MY_BEGIN_NAMESPACE(MyNS)

#ifdef USE_EXTERN_THREAD

TestSocket::TestSocket()
{
	SocketHandler aaa(NULL);
	mTcpSocket = MY_NEW TcpSocket(aaa);
}

#endif	// USE_EXTERN_THREAD

MY_END_NAMESPACE