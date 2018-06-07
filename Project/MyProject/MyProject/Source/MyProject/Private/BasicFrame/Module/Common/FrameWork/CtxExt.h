#pragma once

#include "Ctx.h"
#include "MySharedPointer.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GameData;
class EntityData;

class CtxExt : public Ctx
{
protected:
	MySharedPtr<GameData> mGameData;
	MySharedPtr<EntityData> mEntityData;

public:
	CtxExt();

	virtual void construct() override;
	virtual void init() override;
	virtual void dispose() override;

	void setGameData(GameData* gameData);
	MySharedPtr<GameData> getGameData();

	void setEntityData(EntityData* entityData);
	MySharedPtr<EntityData> getEntityData();
};

#define GCtxExt CtxExt::getSingletonPtr()
#define GTableSys GCtxExt->getGameData()
#define GNetMgr GCtxExt->getEntityData()

MY_END_NAMESPACE