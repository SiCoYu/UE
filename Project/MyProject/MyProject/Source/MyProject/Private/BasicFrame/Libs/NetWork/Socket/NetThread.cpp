#include "MyProject.h"
#include "NetThread.h"

#ifdef ENABLE_DETACH

#include "Windows/AllowWindowsPlatformTypes.h"

#include "Sockets/Utility.h"

#include "Windows/HideWindowsPlatformTypes.h"

#include "INetMgr.h"

#ifdef SOCKETS_NAMESPACE
namespace SOCKETS_NAMESPACE {
#endif

NetThread::NetThread(SocketHandler *p)
	: Thread(true)
	, mH(p)
	, mIsExitFlag(false)
{
	// Creator will release
}

NetThread::~NetThread()
{
	if (IsRunning())
	{
		SetRelease(true);
		SetRunning(false);
		Utility::Sleep(5);
	}
}

void NetThread::Run()
{
	while (!mIsExitFlag)
	{
		if (mH->GetCount() > 1 && IsRunning())
		{
			mH->Select(0, 500000);
			((INetMgr*)mH)->recAndSendMsg();
		}

		Utility::Sleep(1000);
	}
	// mSocket now deleted oops
	//  (a socket can only be detached if DeleteByHandler() is true)
	// yeah oops mSocket delete its socket thread, that means this
	// so Socket will no longer delete its socket thread, instead we do this:
	SetDeleteOnExit();
}

void NetThread::setExitFlag(bool exit)
{
	mIsExitFlag = exit;
}

#ifdef SOCKETS_NAMESPACE
} // namespace SOCKETS_NAMESPACE {
#endif

#endif // ENABLE_DETACH