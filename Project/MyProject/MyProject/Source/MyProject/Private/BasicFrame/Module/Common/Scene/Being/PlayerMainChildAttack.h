#pragma once

#include "Engine/EngineTypes.h"		// FHitResult
#include "PlayerChildAttack.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class PlayerMainChildAttack : public PlayerChildAttack
{
	M_DECLARE_CLASS(PlayerMainChildAttack, PlayerChildAttack)

public:
	PlayerMainChildAttack(BeingEntity* entity);

	virtual void overlapToEnter(BeingEntity* bBeingEntity, const FHitResult& SweepResult) override;
	virtual void overlapToStay(BeingEntity* bBeingEntity, const FHitResult& SweepResult) override;
	virtual void overlapToExit(BeingEntity* bBeingEntity, const FHitResult& SweepResult) override;
};

MY_END_NAMESPACE