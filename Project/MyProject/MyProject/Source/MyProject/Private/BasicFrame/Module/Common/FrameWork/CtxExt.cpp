#include "MyProject.h"
#include "CtxExt.h"
#include "GameData.h"
#include "EntityData.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

CtxExt::CtxExt()
{
	this->mGameData.setNull();
	this->mEntityData.setNull();
}

void Ctx::construct()
{
	Super::construct();

	this->mGameData = MySharedPtr<GameData>(MY_NEW GameData());
	this->mEntityData = MySharedPtr<EntityData>(MY_NEW EntityData());
}

void Ctx::init()
{
	Super::init();

	this->mGameData->init();
	this->mEntityData->init();
}

void Ctx::dispose()
{
	this->mGameData->dispose();
	this->mEntityData->dispose();

	Super::dispose();
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