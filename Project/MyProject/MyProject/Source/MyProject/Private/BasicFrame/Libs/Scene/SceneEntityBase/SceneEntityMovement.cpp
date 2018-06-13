#include "MyProject.h"
#include "SceneEntityMovement.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(SceneEntityMovement, GObject)

SceneEntityMovement::SceneEntityMovement(SceneEntityBase* entity)
{
	this->mTypeId = "SceneEntityMovement";

	this->mEntity = entity;
}

void SceneEntityMovement::init()
{

}

void SceneEntityMovement::dispose()
{
	this->mEntity = nullptr;
}

void SceneEntityMovement::onTick(float delta, TickMode tickMode)
{

}
	
MY_END_NAMESPACE