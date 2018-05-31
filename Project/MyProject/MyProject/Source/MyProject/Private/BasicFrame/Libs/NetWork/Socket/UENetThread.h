#ifndef __UENETTHREAD_H
#define __UENETTHREAD_H

#include "MThread.h"
#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class INetMgr;
class MEvent;

/**
 * @brief UE �����̣߳���ʵ����һ�� Task����Ϊ UE �Ѿ�ʵ���˶��̵߳Ļ������̣�ֻ��Ҫ�����������������ˣ����� FRenderingThread ʵ��
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