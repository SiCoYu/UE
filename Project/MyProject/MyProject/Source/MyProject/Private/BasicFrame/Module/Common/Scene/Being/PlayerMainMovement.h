#pragma once

#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"		// FQuat
#include "Math/Rotator.h"	// FRotator

#include "PlayerMovement.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class PlayerMainMovement : public PlayerMovement
{
	M_DECLARE_CLASS(PlayerMainMovement, PlayerMovement)

protected:
	FQuat mForwardRotate;     // 记录当前的前向
	FQuat mRotate;

public:
	PlayerMainMovement(SceneEntityBase* entity);

	virtual void init() override;
	virtual void dispose() override;
	virtual void onPutInPool() override;
	virtual void onTick(float delta, TickMode tickMode) override;
	FQuat getForwardRotate();
	virtual void setForwardRotate(FVector rotate) override;
};

MY_END_NAMESPACE