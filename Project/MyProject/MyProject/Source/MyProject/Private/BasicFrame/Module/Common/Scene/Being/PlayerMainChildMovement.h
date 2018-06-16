#pragma once

#include "PlayerChildMovement.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

class PlayerMainChildMovement : public PlayerChildMovement
{
	M_DECLARE_CLASS(PlayerMainChildMovement, PlayerChildMovement)

public:
	PlayerMainChildMovement(SceneEntityBase* entity);

	override void init();
	override void dispose();
	virtual void onPutInPool() override;
	virtual void onTick(float delta, TickMode tickMode) override;
};

MY_END_NAMESPACE