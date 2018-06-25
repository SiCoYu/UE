#pragma once

#include <list>
#include "ITickedObject.h"
#include "IDelayTask.h"
#include "TickMode.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class DelayTaskMgr : public GObject/*, public ITickedObject*/
{
protected:
	int mFrameInterval;	// ֡���
	int mTaskNumPerFrameInterval;	// ÿһ��֡���ִ����������
	int mCurTaskNum;				// ��ǰִ�е���������
	int mPreFrame;	// ֮ǰ֡
	int mCurFrame;	// ��ǰ֡

	std::list<IDelayTask*> mDelayTaskList;

public:
	DelayTaskMgr();
	virtual ~DelayTaskMgr();

public:
	void init();
	void dispose();

	virtual void onTick(float delta, TickMode tickMode) override;
	void addTask(IDelayTask* task);
	void execTask();
};

MY_END_NAMESPACE