#include "MyProject.h"
#include "SceneEntityMovement.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(EntityMgrBase, DelayPriorityHandleMgrBase)

SceneEntityMovement(SceneEntityBase entity)
{
	mTypeId = "SceneEntityMovement";
	this->mEntity = entity;
}

virtual void init()
{

}

virtual void dispose()
{
	this->mEntity = nullptr;
}

virtual void onTick(float delta, TickMode tickMode)
{

}
	
MY_END_NAMESPACE