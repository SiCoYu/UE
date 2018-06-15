#pragma once

#include "PlayerChildAttack.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

class PlayerOtherChildAttack : public PlayerChildAttack
{
public:
	PlayerOtherChildAttack(SceneEntityBase* entity);
};

MY_END_NAMESPACE