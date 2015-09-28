#ifndef __UENETTHREAD_H
#define __UENETTHREAD_H

#include "MyProject.h"

class INetMgr;

/**
 * @brief UE 网络线程，其实就是一个 Task，因为 UE 已经实现了多线程的基本流程，只需要向里面添加任务就行了，参照 FRenderingThread 实现
 */
class UENetThread : public FRunnable
{
private:
	INetMgr* m_pNetMgr;
	bool m_ExitFlag;

public:
	UENetThread(INetMgr* pNetMgr);
	virtual ~UENetThread();

	FEvent* m_pTaskGraphBoundSyncEvent;

	virtual bool Init(void) override;
	virtual void Exit(void) override;
	virtual uint32 Run(void) override;

	void setExitFlag(bool exit);
};

void RenderingThreadMain(FEvent* TaskGraphBoundSyncEvent);

#endif