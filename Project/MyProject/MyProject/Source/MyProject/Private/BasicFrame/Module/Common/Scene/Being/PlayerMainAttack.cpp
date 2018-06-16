#include "MyProject.h"
#include "PlayerMainAttack.h"
#include "BeingEntity.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(BeingEntity, SceneEntityBase)

PlayerMainAttack::PlayerMainAttack(BeingEntity* entity)
{
	Super(entity);
}

MY_END_NAMESPACE