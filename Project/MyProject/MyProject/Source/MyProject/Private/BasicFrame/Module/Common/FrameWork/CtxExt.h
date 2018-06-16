#pragma once

#include "Ctx.h"
#include "MySharedPointer.h"

MY_BEGIN_NAMESPACE(MyNS)

class ProjectData;
class EntityData;

class CtxExt : public Ctx
{
protected:
	MySharedPtr<ProjectData> mProjectData;
	MySharedPtr<EntityData> mEntityData;

public:
	CtxExt();

	virtual void construct() override;
	virtual void init() override;
	virtual void dispose() override;

	void setProjectData(ProjectData* gameData);
	MySharedPtr<ProjectData> getProjectData();

	void setEntityData(EntityData* entityData);
	MySharedPtr<EntityData> getEntityData();
};

#define GCtxExt ((CtxExt*)(CtxExt::getSingletonPtr()))
#define GProjectData GCtxExt->getProjectData()
#define GEntityData GCtxExt->getEntityData()
#define GPlayerMgr GCtxExt->getProjectData->getPlayerMgr()

MY_END_NAMESPACE