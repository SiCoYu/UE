#include "MyProject.h"
#include "PlayerMovement.h"
#include "SceneEntityBase.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerMovement, BeingEntityMovement)

PlayerMovement::PlayerMovement(SceneEntityBase* entity)
{
	Super(entity);
}

MY_END_NAMESPACE