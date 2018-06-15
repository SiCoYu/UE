#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerMainChildAttack : PlayerChildAttack
{
	public PlayerMainChildAttack(BeingEntity entity)
		: base(entity)
	{

	}

	override public void overlapToEnter(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
	{
		
	}

	override public void overlapToStay(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
	{
		
	}

	override public void overlapToExit(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
	{
		
	}

	override public void overlapToEnter2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
	{
		
	}

	override public void overlapToStay2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
	{
		
	}

	override public void overlapToExit2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
	{

	}
	
};

MY_END_NAMESPACE