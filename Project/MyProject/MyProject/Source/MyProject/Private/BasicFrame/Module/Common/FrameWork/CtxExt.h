#pragma once

#include "Ctx.h"
#include "MySharedPointer.h"

MY_BEGIN_NAMESPACE(MyNS)

class PlayerData;
class EntityData;

class CtxExt : public Ctx
{
protected:
	MySharedPtr<PlayerData> mPlayerData;
	MySharedPtr<EntityData> mEntityData;

public:
	CtxExt();

	virtual void construct() override;
	virtual void init() override;
	virtual void dispose() override;

	void setPlayerData(PlayerData* gameData);
	MySharedPtr<PlayerData> getPlayerData();

	void setEntityData(EntityData* entityData);
	MySharedPtr<EntityData> getEntityData();
};

#define GCtxExt ((CtxExt*)(CtxExt::getSingletonPtr()))
#define GPlayerData GCtxExt->getPlayerData()
#define GEntityData GCtxExt->getEntityData()
#define GPlayerMgr GEntityData->getPlayerMgr()

MY_END_NAMESPACE