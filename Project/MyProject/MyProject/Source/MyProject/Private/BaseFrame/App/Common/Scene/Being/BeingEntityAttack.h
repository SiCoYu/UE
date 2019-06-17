#pragma once

#include "Engine/EngineTypes.h"		// FHitResult

#include "SceneEntityAttack.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class BeingEntity;

/**
 * @brief 攻击控制器，控制攻击逻辑
 */
class BeingEntityAttack : public SceneEntityAttack
{
	M_DECLARE_CLASS(BeingEntityAttack, SceneEntityAttack)

protected:
	BeingEntity* mEntity;

public:
	BeingEntityAttack(SceneEntityBase* entity);
	
	virtual void init();
	virtual void dispose();
	virtual void onPutInPool();

	virtual void onTick(float delta, TickMode tickMode);
	virtual void overlapToEnter(BeingEntity* bBeingEntity, const FHitResult& SweepResult);
	virtual void overlapToStay(BeingEntity* bBeingEntity, const FHitResult& SweepResult);
	virtual void overlapToExit(BeingEntity* bBeingEntity, const FHitResult& SweepResult);
};

MY_END_NAMESPACE