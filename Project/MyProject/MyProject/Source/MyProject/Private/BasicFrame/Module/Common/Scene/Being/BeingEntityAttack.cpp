#include "MyProject.h"
#include "BeingEntityAttack.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

BeingEntityAttack::BeingEntityAttack(BeingEntity* entity)
{
	mEntity = entity;
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

void BeingEntityAttack::overlapToEnter(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
{
	
}

void BeingEntityAttack::overlapToStay(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
{
	
}

void BeingEntityAttack::overlapToExit(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
{
	
}

void BeingEntityAttack::overlapToEnter2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
{
	
}

void BeingEntityAttack::overlapToStay2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
{
	
}

void BeingEntityAttack::overlapToExit2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
{
	
}

MY_END_NAMESPACE