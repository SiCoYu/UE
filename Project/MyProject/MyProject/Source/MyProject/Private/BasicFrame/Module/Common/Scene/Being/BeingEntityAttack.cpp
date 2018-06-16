#include "MyProject.h"
#include "BeingEntityAttack.h"
#include "BeingEntity.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(BeingEntityAttack, SceneEntityAttack)

BeingEntityAttack::BeingEntityAttack(BeingEntity* entity)
{
	this->mEntity = entity;
}

void BeingEntityAttack::init()
{

}

void BeingEntityAttack::dispose()
{

}

void BeingEntityAttack::onPutInPool()
{

}

void BeingEntityAttack::onTick(float delta, TickMode tickMode)
{

}

void BeingEntityAttack::overlapToEnter(BeingEntity* bBeingEntity, const FHitResult& SweepResult)
{
	
}

void BeingEntityAttack::overlapToStay(BeingEntity* bBeingEntity, const FHitResult& SweepResult)
{
	
}

void BeingEntityAttack::overlapToExit(BeingEntity* bBeingEntity, const FHitResult& SweepResult)
{
	
}

MY_END_NAMESPACE