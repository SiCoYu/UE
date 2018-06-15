#pragma once

#include "PlayerChildMovement.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class PlayerOtherChildMovement : public PlayerChildMovement
{
public:
	PlayerOtherChildMovement(SceneEntityBase* entity);

	virtual void onTick(float delta, TickMode tickMode) override;
};

MY_END_NAMESPACE