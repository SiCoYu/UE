#pragma once

#include "GameFramework/Actor.h"

#include "PhysicsEngine/PhysicsConstraintActor.h"
#include "PhysicsEngine/ConstraintInstance.h"	// FConstraintInstance
#include "Engine/EngineTypes.h"	// ELinearConstraintMotion
#include "PhysicsEngine/PhysicsConstraintComponent.h"	// UPhysicsConstraintComponent
#include "Containers/UnrealString.h"	// FString

#include "MyActorBase.generated.h"

UCLASS(config = Game)
class AMyActorBase : public AActor
{
	GENERATED_BODY()

public:
	AMyActorBase(const FObjectInitializer& ObjectInitializer);

	// https://wiki.unrealengine.com/Physics_Constraints,_Create_New_Constraints_Dynamically_During_Runtime
	void CreateNewPhysicsConstraintBetween(AStaticMeshActor* RootSMA, AStaticMeshActor* TargetSMA);

	static FORCEINLINE void SetLinearLimits(
		FConstraintInstance& Constraint,
		bool bDisableCollision,
		const uint8 XLim, const uint8 YLim, const uint8 ZLim,
		const float Size,
		bool SoftLimit = true,
		const float SoftStiffness = 0,
		const float SoftDampening = 0
		)
	{
		Constraint.SetDisableCollision(bDisableCollision);

		switch (XLim)
		{
		case 0: Constraint.SetLinearXMotion(ELinearConstraintMotion::LCM_Free); break;
		case 1: Constraint.SetLinearXMotion(ELinearConstraintMotion::LCM_Limited); break;
		case 2: Constraint.SetLinearXMotion(ELinearConstraintMotion::LCM_Locked); break;
		}
		switch (YLim)
		{
		case 0: Constraint.SetLinearYMotion(ELinearConstraintMotion::LCM_Free); break;
		case 1: Constraint.SetLinearYMotion(ELinearConstraintMotion::LCM_Limited); break;
		case 2: Constraint.SetLinearYMotion(ELinearConstraintMotion::LCM_Locked); break;
		}
		switch (ZLim)
		{
		case 0: Constraint.SetLinearZMotion(ELinearConstraintMotion::LCM_Free); break;
		case 1: Constraint.SetLinearZMotion(ELinearConstraintMotion::LCM_Limited); break;
		case 2: Constraint.SetLinearZMotion(ELinearConstraintMotion::LCM_Locked); break;
		}

		Constraint.SetLinearLimitSize(Size);

		if (SoftLimit) Constraint.bLinearLimitSoft_DEPRECATED = 1;
		else Constraint.bLinearLimitSoft_DEPRECATED = 0;

		Constraint.LinearLimitStiffness_DEPRECATED = SoftStiffness;
		Constraint.LinearLimitDamping_DEPRECATED = SoftDampening;
	}

	static FORCEINLINE void SetAngularLimits(
		FConstraintInstance& Constraint,
		const uint8 S1Lim, const uint8 S2Lim, const uint8 TLim,
		const float Swing1LimitAngle,
		const float Swing2LimitAngle,
		const float TwistLimitAngle,

		bool SoftSwingLimit = true, bool SoftTwistLimit = true,
		const float SwingStiff = 0, const float SwingDamp = 0,
		const float TwistStiff = 0, const float TwistDamp = 0
		)
	{
		switch (S1Lim)
		{
		case 0: Constraint.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Free, Swing1LimitAngle); break;
		case 1: Constraint.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Limited, Swing1LimitAngle); break;
		case 2: Constraint.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, Swing1LimitAngle); break;
		}
		switch (S2Lim)
		{
		case 0: Constraint.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, Swing2LimitAngle); break;
		case 1: Constraint.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Limited, Swing2LimitAngle); break;
		case 2: Constraint.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, Swing2LimitAngle); break;
		}
		switch (TLim)
		{
		case 0: Constraint.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, TwistLimitAngle); break;
		case 1: Constraint.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Limited, TwistLimitAngle); break;
		case 2: Constraint.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, TwistLimitAngle); break;
		}

		if (SoftSwingLimit) Constraint.bSwingLimitSoft_DEPRECATED = 1;
		else Constraint.bSwingLimitSoft_DEPRECATED = 0;

		if (SoftTwistLimit) Constraint.bTwistLimitSoft_DEPRECATED = 1;
		else Constraint.bTwistLimitSoft_DEPRECATED = 0;

		Constraint.SwingLimitStiffness_DEPRECATED = SwingStiff;
		Constraint.SwingLimitDamping_DEPRECATED = SwingDamp;
		Constraint.TwistLimitStiffness_DEPRECATED = TwistStiff;
		Constraint.TwistLimitDamping_DEPRECATED = TwistDamp;
	}
};