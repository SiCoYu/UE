#ifndef __UENETTHREAD_H
#define __UENETTHREAD_H

#include "MyProject.h"

class INetMgr;

/**
 * @brief UE �����̣߳���ʵ����һ�� Task����Ϊ UE �Ѿ�ʵ���˶��̵߳Ļ������̣�ֻ��Ҫ�����������������ˣ����� FRenderingThread ʵ��
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