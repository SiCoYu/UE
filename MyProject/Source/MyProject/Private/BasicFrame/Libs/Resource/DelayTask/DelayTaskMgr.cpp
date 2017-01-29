#include "MyProject.h"
#include "DelayTaskMgr.h"
#include "Common.h"

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

void DelayTaskMgr::onTick(float delta)
{
	this->mCurFrame = GSystemFrameData->getTotalFrameCount();

	if (this->mPreFrame + this->mFrameInterval <= this->mCurFrame)
	{
		this->mPreFrame = this->mCurFrame;
		this->mCurTaskNum = 0;
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

	}
}