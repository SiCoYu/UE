#include "MyProject.h"
#include "PlayerRender.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(SceneEntityMovement, GObject)

PlayerAttack::PlayerAttack(BeingEntity* entity)
{
	Super(entity);
}

MY_END_NAMESPACE