#include "MyProject.h"
#include "GameEventCmd.h"
#include "IDispatchObject.h"
#include "CtxExt.h"
#include "ModuleSys.h"
#include "ModuleId.h"

MY_BEGIN_NAMESPACE(MyNS)

GameEventCmd::GameEventCmd()
{

}

void GameEventCmd::init()
{

}

void GameEventCmd::dispose()
{

}

void GameEventCmd::onCoreInitedHandle(uint eventId, IDispatchObject* dispObj)
{
	GModuleSys->loadModule(ModuleId::GAMEMN);
}

MY_END_NAMESPACE