#include "MyProject.h"
#include "PlayerOtherAttack.h"
#include "SceneEntityBase.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(PlayerOtherAttack, BeingEntityAttack)

PlayerOtherAttack::PlayerOtherAttack(SceneEntityBase* entity)
{
	Super(entity);
}

MY_END_NAMESPACE