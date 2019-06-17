#include "MyProject.h"
#include "DelayTaskMgr.h"
#include "Prequisites.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayTaskMgr::DelayTaskMgr()
{
	this->mFrameInterval = 1;
	this->mTaskNumPerFrameInterval = 1;
	this->mCurTaskNum = 0;
	this->mPreFrame = 0;
	this->mCurFrame = 0;
}

DelayTaskMgr::~DelayTaskMgr()
{

}

void DelayTaskMgr::init()
{

}

void DelayTaskMgr::dispose()
{

}

void DelayTaskMgr::onTick(float delta, TickMode tickMode)
{
	this->mCurFrame = GSystemFrameData->getTotalFrameCount();

	if (this->mPreFrame + this->mFrameInterval <= this->mCurFrame)
	{
		this->mPreFrame = this->mCurFrame;
		this->mCurTaskNum = 0;

		this->execTask();
	}
}

void DelayTaskMgr::addTask(IDelayTask* task)
{
	if (this->mCurTaskNum < this->mTaskNumPerFrameInterval)
	{
		++this->mCurTaskNum;
		task->delayExec();
	}
	else
	{
		this->mDelayTaskList.push_back(task);
	}
}

void DelayTaskMgr::execTask()
{
	IDelayTask* task = nullptr;

	while (this->mCurTaskNum < this->mTaskNumPerFrameInterval)
	{
		if (this->mDelayTaskList.size() > 0)
		{
			task = this->mDelayTaskList.front();
			this->mDelayTaskList.pop_front();
			task->delayExec();
		}

		++this->mCurTaskNum;
	}
}

MY_END_NAMESPACE