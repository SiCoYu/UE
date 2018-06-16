#include "MyProject.h"
#include "PlayerMainChildAttack.h"
#include "BeingEntity.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerMainChildAttack::PlayerMainChildAttack(BeingEntity* entity)
{
	Super(entity);
}

void PlayerMainChildAttack::overlapToEnter(BeingEntity* bBeingEntity, const FHitResult& SweepResult)
{

}

void PlayerMainChildAttack::overlapToStay(BeingEntity* bBeingEntity, const FHitResult& SweepResult)
{

}

void PlayerMainChildAttack::overlapToExit(BeingEntity* bBeingEntity, const FHitResult& SweepResult)
{

}

MY_END_NAMESPACE