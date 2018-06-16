#include "MyProject.h"
#include "PlayerRender.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerMainChildMovement::PlayerMainChildMovement(SceneEntityBase* entity)
{
	Super(entity);
}

void PlayerMainChildMovement::init()
{
	Super::init();
}

void PlayerMainChildMovement::dispose()
{
	Super::dispose();
}

void PlayerMainChildMovement::onPutInPool()
{
	Super::onPutInPool();
}

void PlayerMainChildMovement::onTick(float delta, TickMode tickMode)
{
	Super::onTick(delta, tickMode);
}

MY_END_NAMESPACE