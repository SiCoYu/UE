#pragma once

#include "PlayerChildMovement.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

class PlayerOtherChildMovement : public PlayerChildMovement
{
	M_DECLARE_CLASS(PlayerOtherChildMovement, PlayerChildMovement)

public:
	PlayerOtherChildMovement(SceneEntityBase* entity);

	virtual void onTick(float delta, TickMode tickMode) override;
};

MY_END_NAMESPACE