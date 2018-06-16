#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerMainChildAttack : PlayerChildAttack
{
public:
	PlayerMainChildAttack(BeingEntity entity)
		: base(entity)
	{

	}

	virtual void overlapToEnter(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo) override
	{
		
	}

	virtual void overlapToStay(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo) override
	{
		
	}

	virtual void overlapToExit(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo) override
	{
		
	}

	virtual void overlapToEnter2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo) override
	{
		
	}

	virtual void overlapToStay2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo) override
	{
		
	}

	virtual void overlapToExit2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo) override
	{

	}
};

MY_END_NAMESPACE