#ifndef __UENETTHREAD_H
#define __UENETTHREAD_H

#include "MThread.h"
#include <string>

class INetMgr;
class MEvent;

/**
 * @brief UE �����̣߳���ʵ����һ�� Task����Ϊ UE �Ѿ�ʵ���˶��̵߳Ļ������̣�ֻ��Ҫ�����������������ˣ����� FRenderingThread ʵ��
 */
class UENetThread : public MThread
{
private:
	INetMgr* mNetMgr;
	bool mIsExitFlag;
	MEvent* mSyncEvent;

public:
	UENetThread(INetMgr* pNetMgr, std::string threadName);
	virtual ~UENetThread();

	MEvent* getSyncEventPtr();
	virtual bool Init(void) override;
	virtual void Exit(void) override;
	virtual uint32 Run(void) override;
};

#endif