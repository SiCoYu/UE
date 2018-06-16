#include "MyProject.h"
#include "PlayerMainMovement.h"
#include "SceneEntityBase.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerMainMovement, PlayerMovement)

PlayerMainMovement::PlayerMainMovement(SceneEntityBase* entity)
{
	Super(entity)

	this->mForwardRotate = UtilMath::UnitQuat;
	this->mRotate = UtilMath::UnitQuat;
}

void PlayerMainMovement::init()
{
	Super::init();
}

void PlayerMainMovement::dispose()
{
	Super::dispose();
}

void PlayerMainMovement::onPutInPool()
{
	Super::onPutInPool();
}

void PlayerMainMovement::onTick(float delta, TickMode tickMode)
{
	Super::onTick(delta, tickMode);
}

FQuat PlayerMainMovement::getForwardRotate()
{
	return this->mForwardRotate;
}

void PlayerMainMovement::setForwardRotate(FVector rotate)
{
	this->mForwardRotate = FQuat.Euler(rotate);
}

MY_END_NAMESPACE