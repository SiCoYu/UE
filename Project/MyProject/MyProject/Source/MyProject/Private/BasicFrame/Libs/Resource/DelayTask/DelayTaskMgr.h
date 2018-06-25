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
	int mFrameInterval;	// 帧间隔
	int mTaskNumPerFrameInterval;	// 每一个帧间隔执行任务数量
	int mCurTaskNum;				// 当前执行的任务数量
	int mPreFrame;	// 之前帧
	int mCurFrame;	// 当前帧

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