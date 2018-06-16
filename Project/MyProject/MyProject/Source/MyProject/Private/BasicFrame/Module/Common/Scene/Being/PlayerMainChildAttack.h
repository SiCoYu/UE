#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerMainChildAttack : PlayerChildAttack
{
	M_DECLARE_CLASS(BeingEntity, SceneEntityBase)

public:
	PlayerMainChildAttack(BeingEntity entity)
		: base(entity)
	{

	}

	virtual void overlapToEnter(BeingEntity bBeingEntity, const FHitResult& SweepResult) override
	{
		
	}

	virtual void overlapToStay(BeingEntity bBeingEntity, const FHitResult& SweepResult) override
	{
		
	}

	virtual void overlapToExit(BeingEntity bBeingEntity, const FHitResult& SweepResult) override
	{
		
	}
};

MY_END_NAMESPACE