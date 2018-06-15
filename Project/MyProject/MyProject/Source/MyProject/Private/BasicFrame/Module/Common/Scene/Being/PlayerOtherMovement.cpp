#include "MyProject.h"
#include "PlayerOtherMovement.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerOtherMovement::PlayerOtherMovement(SceneEntityBase* entity)
		: base(entity)
{

}

void PlayerOtherMovement::onTick(float delta, TickMode tickMode)
{
	base.onTick(delta, tickMode);
}

MY_END_NAMESPACE