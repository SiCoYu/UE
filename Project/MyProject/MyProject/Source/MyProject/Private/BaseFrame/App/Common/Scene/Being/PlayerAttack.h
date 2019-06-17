#pragma once

#include "BeingEntityAttack.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class PlayerAttack : public BeingEntityAttack
{
	M_DECLARE_CLASS(PlayerAttack, BeingEntityAttack)

public:
	PlayerAttack(BeingEntity* entity);
};

MY_END_NAMESPACE