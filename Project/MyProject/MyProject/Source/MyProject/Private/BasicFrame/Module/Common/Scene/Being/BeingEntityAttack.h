#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 攻击控制器，控制攻击逻辑
 */
class BeingEntityAttack
{
	protected BeingEntity mEntity;

	public BeingEntityAttack(BeingEntity entity)
	{
		mEntity = entity;
	}

	virtual public void init()
	{

	}

	virtual public void dispose()
	{

	}

	virtual public void onPutInPool()
	{

	}

	virtual public void onTick(float delta, TickMode tickMode)
	{

	}

	virtual public void overlapToEnter(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
	{
		
	}

	virtual public void overlapToStay(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
	{
		
	}

	virtual public void overlapToExit(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
	{
		
	}

	virtual public void overlapToEnter2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
	{
		
	}

	virtual public void overlapToStay2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
	{
		
	}

	virtual public void overlapToExit2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
	{
		
	}
};

MY_END_NAMESPACE