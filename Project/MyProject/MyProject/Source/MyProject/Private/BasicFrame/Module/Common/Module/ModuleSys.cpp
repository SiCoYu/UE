#include "MyProject.h"
#include "ModuleSys.h"
#include "ModuleHandleItem.h"
#include "GameModule.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

ModuleSys::ModuleSys()
{
	this->_registerHandler();
}

void ModuleSys::init()
{

}

void ModuleSys::dispose()
{

}

void ModuleSys::_registerHandler()
{
	ModuleHandleItem item;

	item.mModuleId = ModuleId::GAMEMN;
	this->mType2ItemDic[item.mModuleId] = item;
}

void ModuleSys::loadModule(ModuleId moduleId)
{
	if (!this->mType2ItemDic[moduleId].mIsLoaded)
	{
		this->mType2ItemDic[moduleId].mIsLoaded = true;

		if (ModuleId::GAMEMN == moduleId)
		{
			this->mType2ItemDic[moduleId]->mModule = MY_NEW GameModule();
			this->mType2ItemDic[moduleId]->mModule->init();
		}
	}
	else
	{

	}
}

void ModuleSys::unloadModule(ModuleId moduleId)
{
	this->mType2ItemDic[moduleId].mIsLoaded = false;
	MY_SAFE_DISPOSE(this->mType2ItemDic[moduleId]->mModule);
}

MY_END_NAMESPACE