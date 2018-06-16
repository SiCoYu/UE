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
	Super::onTick(delta, tickMode);
}

MY_END_NAMESPACE