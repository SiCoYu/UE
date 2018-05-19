#include "MyProject.h"
#include "GameTimeCmdHandle.h"

GameTimeCmdHandle::GameTimeCmdHandle()
{

}

void GameTimeCmdHandle::init()
{
    Super::init();

    this->addParamHandle(stTimerUserCmd.GAMETIME_TIMER_USERCMD_PARA, Ctx.msInstance.mTimerMsgHandle.receiveMsg7f);
    this->addParamHandle(stTimerUserCmd.REQUESTUSERGAMETIME_TIMER_USERCMD_PARA, Ctx.msInstance.mTimerMsgHandle.receiveMsg8f);
}

void GameTimeCmdHandle::dispose()
{
    this.removeParamHandle(stTimerUserCmd.GAMETIME_TIMER_USERCMD_PARA, Ctx.msInstance.mTimerMsgHandle.receiveMsg7f);
    this.removeParamHandle(stTimerUserCmd.REQUESTUSERGAMETIME_TIMER_USERCMD_PARA, Ctx.msInstance.mTimerMsgHandle.receiveMsg8f);

	Super::dispose();
}