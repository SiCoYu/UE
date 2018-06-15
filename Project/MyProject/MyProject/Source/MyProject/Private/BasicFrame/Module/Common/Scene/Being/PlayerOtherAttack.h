#pragma once

#include "BeingEntityAttack.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

public class PlayerOtherAttack : BeingEntityAttack
{
public:
	PlayerOtherAttack(SceneEntityBase* entity)
		: base(entity)
	{

	}
};

MY_END_NAMESPACE