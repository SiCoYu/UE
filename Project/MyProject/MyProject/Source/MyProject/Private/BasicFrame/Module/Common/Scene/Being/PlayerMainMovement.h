#pragma once

#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"		// FQuat
#include "Math/Rotator.h"	// FRotator

#include "SceneEntityBase.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerMainMovement : PlayerMovement
{
	M_DECLARE_CLASS(BeingEntity, SceneEntityBase)

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