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
	this->advance(GSystemTimeData->getDeltaSec());
}

void ProcessSys::advance(float delta)
{
	//Ctx.mInstance.mFrameCollideMgr.clear();
	GSystemFrameData->nextFrame(delta);
	//Ctx.mInstance.mLuaSystem.advance(delta);        // lua 脚本 advance
	GTickMgr->advance(delta);            // 心跳
	GTimerMgr->advance(delta);           // 定时器
	GFrameTimerMgr->advance(delta);      // 帧定时器
}

MY_END_NAMESPACE