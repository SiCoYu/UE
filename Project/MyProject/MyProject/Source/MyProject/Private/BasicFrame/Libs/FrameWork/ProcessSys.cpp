#include "MyProject.h"
#include "ProcessSys.h"
#include "Prequisites.h"

MY_BEGIN_NAMESPACE(MyNS)

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
	GTickMgr->Advance(delta);            // 心跳
	GTimerMgr->Advance(delta);           // 定时器
	GFrameTimerMgr->Advance(delta);      // 帧定时器
}

MY_END_NAMESPACE