#pragma once

#include "BeingEntityAttack.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerMainAttack : BeingEntityAttack
{
	M_DECLARE_CLASS(BeingEntity, SceneEntityBase)

public:
	PlayerMainAttack(BeingEntity* entity);
};

MY_END_NAMESPACE