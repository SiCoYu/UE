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
protected:
	BeingEntity* mEntity;

public:
	BeingEntityAttack(BeingEntity* entity);
	
	virtual void init();
	virtual void dispose();
	virtual void onPutInPool();

	virtual void onTick(float delta, TickMode tickMode);
	virtual void overlapToEnter(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo);
	virtual void overlapToStay(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo);
	virtual void overlapToExit(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo);
	virtual void overlapToEnter2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo);
	virtual void overlapToStay2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo);
	virtual void overlapToExit2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo);
};

MY_END_NAMESPACE