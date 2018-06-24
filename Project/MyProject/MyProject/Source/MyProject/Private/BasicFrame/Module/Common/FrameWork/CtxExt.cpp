#include "MyProject.h"
#include "CtxExt.h"
#include "PlayerData.h"
#include "EntityData.h"
#include "ModuleSys.h"
#include "DataDelegate.h"
#include "DataEventCmd.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

// 偏特化，这样构造的时候，即使通过多次继承 Singleton ，也会构造正确的类
// error C2371: 'msSingleton': redefinition; different basic types
//template<> CtxExt* CtxExt::Singleton<CtxExt>::msSingleton = 0;

CtxExt::CtxExt()
{
	this->mPlayerData.setNull();
	this->mEntityData.setNull();
	this->mModuleSys.setNull();
	this->mGlobalDelegate.setNull();
	this->mGlobalEventCmd.setNull();
}

void CtxExt::construct()
{
	Ctx::construct();

	this->mPlayerData = MySharedPtr<PlayerData>(MY_NEW PlayerData());
	this->mEntityData = MySharedPtr<EntityData>(MY_NEW EntityData());
	this->mModuleSys = MySharedPtr<ModuleSys>(MY_NEW ModuleSys());
	this->mDataDelegate = MySharedPtr<GlobalDelegate>(MY_NEW DataDelegate());
	this->mDataEventCmd = MySharedPtr<GlobalEventCmd>(MY_NEW DataEventCmd());
}

void CtxExt::init()
{
	Ctx::init();

	this->mPlayerData->init();
	this->mEntityData->init();
	this->mModuleSys->init();
	this->mDataDelegate->init();
	this->mDataEventCmd->init();
}

void CtxExt::dispose()
{
	this->mPlayerData->dispose();
	this->mEntityData->dispose();
	this->mModuleSys->dispose();
	this->mDataDelegate->dispose();
	this->mDataEventCmd->dispose();

	this->mPlayerData.setNull();
	this->mEntityData.setNull();
	this->mModuleSys->setNull();
	this->mDataDelegate->setNull();
	this->mDataEventCmd->setNull();

	Ctx::dispose();
}

void CtxExt::setPlayerData(PlayerData* gameData)
{
	this->mPlayerData = gameData;
}

MySharedPtr<PlayerData> CtxExt::getPlayerData()
{
	return this->mPlayerData;
}

void CtxExt::setEntityData(EntityData* entityData)
{
	this->mEntityData = entityData;
}

MySharedPtr<EntityData> CtxExt::getEntityData()
{
	return this->mEntityData;
}

void CtxExt::setModuleSys(ModuleSys* moduleSys)
{
	this->mModuleSys = moduleSys;
}

MySharedPtr<ModuleSys> CtxExt::getModuleSys()
{
	return this->mModuleSys;
}

MySharedPtr<DataDelegate> getDataDelegate()
{
	return this->mDataDelegate;
}

MySharedPtr<DataEventCmd> getDataEventCmd()
{
	return this->mDataEventCmd;
}

MY_END_NAMESPACE