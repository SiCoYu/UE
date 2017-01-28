#include "MyProject.h"
#include "ProcessSys.h"
#include "Common.h"

ProcessSys::ProcessSys()
{

}

void ProcessSys::init()
{

}

void ProcessSys::dispose()
{

}


void ProcessSys::ProcessNextFrame()
{
	GSystemTimeData->nextFrame();
	this->Advance(GSystemTimeData->getDeltaSec());
}

void ProcessSys::Advance(float delta)
{
	//Ctx.mInstance.mFrameCollideMgr.clear();
	GSystemFrameData->nextFrame(delta);
	//Ctx.mInstance.mLuaSystem.advance(delta);        // lua 脚本 Advance
	//Ctx.mInstance.mTickMgr.Advance(delta);            // 心跳
	//Ctx.mInstance.mTimerMgr.Advance(delta);           // 定时器
	//Ctx.mInstance.mFrameTimerMgr.Advance(delta);      // 帧定时器
}