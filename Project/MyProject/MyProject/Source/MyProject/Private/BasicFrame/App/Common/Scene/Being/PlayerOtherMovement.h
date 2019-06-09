#pragma once

#include "BeingEntityMovement.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

class PlayerOtherMovement : public BeingEntityMovement
{
	M_DECLARE_CLASS(PlayerOtherMovement, BeingEntityMovement)

public:
	PlayerOtherMovement(SceneEntityBase* entity);

	virtual void onTick(float delta, TickMode tickMode) override;
};

MY_END_NAMESPACE