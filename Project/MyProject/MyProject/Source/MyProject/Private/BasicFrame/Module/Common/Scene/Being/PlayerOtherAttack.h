#pragma once

#include "BeingEntityAttack.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

class PlayerOtherAttack : public BeingEntityAttack
{
	M_DECLARE_CLASS(PlayerOtherAttack, BeingEntityAttack)

public:
	PlayerOtherAttack(SceneEntityBase* entity);
};

MY_END_NAMESPACE