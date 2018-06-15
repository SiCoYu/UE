#include "MyProject.h"
#include "PlayerOtherChildMovement.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerOtherChildMovement::PlayerOtherChildMovement(SceneEntityBase* entity)
	: base(entity)
{

}

void PlayerOtherChildMovement::onTick(float delta, TickMode tickMode)
{
	base.onTick(delta, tickMode);
}

MY_END_NAMESPACE