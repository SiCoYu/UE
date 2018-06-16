#include "MyProject.h"
#include "PlayerOtherMovement.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerOtherMovement, BeingEntityMovement)

PlayerOtherMovement::PlayerOtherMovement(SceneEntityBase* entity)
{
	Super(entity);
}

void PlayerOtherMovement::onTick(float delta, TickMode tickMode)
{
	Super::onTick(delta, tickMode);
}

MY_END_NAMESPACE