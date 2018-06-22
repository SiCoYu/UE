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

	void setProjectData(PlayerData* gameData);
	MySharedPtr<PlayerData> getProjectData();

	void setEntityData(EntityData* entityData);
	MySharedPtr<EntityData> getEntityData();
};

#define GCtxExt ((CtxExt*)(CtxExt::getSingletonPtr()))
#define GProjectData GCtxExt->getProjectData()
#define GEntityData GCtxExt->getEntityData()
#define GPlayerMgr GProjectData->getPlayerMgr()

MY_END_NAMESPACE