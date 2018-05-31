#ifndef __UENETTHREAD_H
#define __UENETTHREAD_H

#include "MThread.h"
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class INetMgr;
class MEvent;

/**
 * @brief UE 网络线程，其实就是一个 Task，因为 UE 已经实现了多线程的基本流程，只需要向里面添加任务就行了，参照 FRenderingThread 实现
 */
class UENetThread : public MThread
{
private:
	INetMgr* mNetMgr;
	MEvent* mSyncEvent;

public:
	UENetThread(INetMgr* pNetMgr, std::string threadName);
	virtual ~UENetThread();

	MEvent* getSyncEventPtr();
	virtual bool Init(void) override;
	virtual void Exit(void) override;
	virtual uint32 Run(void) override;
};

MY_END_NAMESPACE

#endif