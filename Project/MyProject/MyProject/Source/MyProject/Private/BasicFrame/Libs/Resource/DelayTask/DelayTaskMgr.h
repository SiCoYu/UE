#pragma once

#include "ITickedObject.h"
#include "IDelayTask.h"
#include <list>

class DelayTaskMgr : public ITickedObject
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
	~DelayTaskMgr();

public:
	void init();
	void dispose();

	virtual void onTick(float delta) override;
	void addTask(IDelayTask* task);
	void execTask();
};