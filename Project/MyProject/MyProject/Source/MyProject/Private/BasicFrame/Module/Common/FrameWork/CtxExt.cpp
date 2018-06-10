#include "MyProject.h"
#include "CtxExt.h"
#include "GameData.h"
#include "EntityData.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

// 偏特化，这样构造的时候，即使通过多次继承 Singleton ，也会构造正确的类
// error C2371: 'msSingleton': redefinition; different basic types
//template<> CtxExt* CtxExt::Singleton<CtxExt>::msSingleton = 0;

CtxExt::CtxExt()
{
	this->mGameData.setNull();
	this->mEntityData.setNull();
}

void CtxExt::construct()
{
	Ctx::construct();

	this->mGameData = MySharedPtr<GameData>(MY_NEW GameData());
	this->mEntityData = MySharedPtr<EntityData>(MY_NEW EntityData());
}

void CtxExt::init()
{
	Ctx::init();

	this->mGameData->init();
	this->mEntityData->init();
}

void CtxExt::dispose()
{
	this->mGameData->dispose();
	this->mEntityData->dispose();

	this->mGameData.setNull();
	this->mEntityData.setNull();

	Ctx::dispose();
}

void CtxExt::setGameData(GameData* gameData)
{
	this->mGameData = gameData;
}

MySharedPtr<GameData> CtxExt::getGameData()
{
	return this->mGameData;
}

void CtxExt::setEntityData(EntityData* entityData)
{
	this->mEntityData = entityData;
}

MySharedPtr<EntityData> CtxExt::getEntityData()
{
	return this->mEntityData;
}

MY_END_NAMESPACE