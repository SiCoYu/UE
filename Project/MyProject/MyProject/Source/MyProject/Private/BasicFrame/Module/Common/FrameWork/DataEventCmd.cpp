#include "MyProject.h"
#include "DataEventCmd.h"
#include "IDispatchObject.h"
#include "CtxExt.h"
#include "ModuleSys.h"
#include "ModuleId.h"

MY_BEGIN_NAMESPACE(MyNS)

DataEventCmd::DataEventCmd()
{

}

void DataEventCmd::init()
{

}

void DataEventCmd::dispose()
{

}

void DataEventCmd::onCoreInitedHandle(uint eventId, IDispatchObject* dispObj)
{
	GModuleSys->loadModule(ModuleId::GAMEMN);
}

MY_END_NAMESPACE