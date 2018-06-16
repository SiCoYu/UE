#include "MyProject.h"
#include "CtxExt.h"
#include "ProjectData.h"
#include "EntityData.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

// 偏特化，这样构造的时候，即使通过多次继承 Singleton ，也会构造正确的类
// error C2371: 'msSingleton': redefinition; different basic types
//template<> CtxExt* CtxExt::Singleton<CtxExt>::msSingleton = 0;

CtxExt::CtxExt()
{
	this->mProjectData.setNull();
	this->mEntityData.setNull();
}

void CtxExt::construct()
{
	Ctx::construct();

	this->mProjectData = MySharedPtr<ProjectData>(MY_NEW ProjectData());
	this->mEntityData = MySharedPtr<EntityData>(MY_NEW EntityData());
}

void CtxExt::init()
{
	Ctx::init();

	this->mProjectData->init();
	this->mEntityData->init();
}

void CtxExt::dispose()
{
	this->mProjectData->dispose();
	this->mEntityData->dispose();

	this->mProjectData.setNull();
	this->mEntityData.setNull();

	Ctx::dispose();
}

void CtxExt::setProjectData(ProjectData* gameData)
{
	this->mProjectData = gameData;
}

MySharedPtr<ProjectData> CtxExt::getProjectData()
{
	return this->mProjectData;
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