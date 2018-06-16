#include "MyProject.h"
#include "PlayerMainAttack.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(SceneEntityMovement, GObject)

PlayerMainAttack::PlayerMainAttack(BeingEntity* entity)
{
	Super(entity);
}

MY_END_NAMESPACE