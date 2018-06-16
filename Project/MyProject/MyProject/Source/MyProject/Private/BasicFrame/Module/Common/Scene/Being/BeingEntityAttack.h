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
	M_DECLARE_CLASS(BeingEntity, SceneEntityBase)

protected:
	BeingEntity* mEntity;

public:
	BeingEntityAttack(BeingEntity* entity);
	
	virtual void init();
	virtual void dispose();
	virtual void onPutInPool();

	virtual void onTick(float delta, TickMode tickMode);
	virtual void overlapToEnter(BeingEntity bBeingEntity, const FHitResult& SweepResult);
	virtual void overlapToStay(BeingEntity bBeingEntity, const FHitResult& SweepResult);
	virtual void overlapToExit(BeingEntity bBeingEntity, const FHitResult& SweepResult);
};

MY_END_NAMESPACE