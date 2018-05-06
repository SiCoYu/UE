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
	if (this->IsRunning())
	{
		this->SetRelease(true);
		this->SetRunning(false);
		Utility::Sleep(5);
	}
}

void NetThread::Run()
{
	while (!this->mIsExitFlag)
	{
		if (this->mH->GetCount() > 1 && this->IsRunning())
		{
			this->mH->Select(0, 500000);
			((INetMgr*)this->mH)->recAndSendMsg();
		}

		Utility::Sleep(1000);
	}
	// mSocket now deleted oops
	//  (a socket can only be detached if DeleteByHandler() is true)
	// yeah oops mSocket delete its socket thread, that means this
	// so Socket will no longer delete its socket thread, instead we do this:
	this->SetDeleteOnExit();
}

void NetThread::setExitFlag(bool exit)
{
	this->mIsExitFlag = exit;
}

#ifdef SOCKETS_NAMESPACE
} // namespace SOCKETS_NAMESPACE {
#endif

#endif // ENABLE_DETACH