#include "MyProject.h"
#include "SceneEntityAttack.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(SceneEntityAttack, GObject)

SceneEntityAttack::SceneEntityAttack(SceneEntityBase* entity)
{
	this->mEntity = entity;
}

void SceneEntityAttack::init()
{

}

void SceneEntityAttack::dispose()
{
	this->mEntity = nullptr;
}

void SceneEntityAttack::onTick(float delta, TickMode tickMode)
{

}
	
MY_END_NAMESPACE