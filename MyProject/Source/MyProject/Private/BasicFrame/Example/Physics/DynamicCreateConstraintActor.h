#pragma once

#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"

#include "PhysicsEngine/PhysicsConstraintActor.h"
#include "PhysicsEngine/ConstraintInstance.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Engine/EngineTypes.h"

#include "DynamicCreateConstraintActor.generated.h"

/**
* @brief https://wiki.unrealengine.com/Physics_Constraints,_Create_New_Constraints_Dynamically_During_Runtime
//A new constraint instance!
FConstraintInstance ConstraintInstance;

//Set Angular Limits of Constraint that was just created
UYourStaticLibrary::SetAngularLimits( //or make functions below non static, put in .h
ConstraintInstance,
1, //swing 1 limited
1, //swing 2 limited
0, //twist is free
60, //swing 1 angle limit
30 //swing 2 angle limit
10 //twist limit (not used cause its free)
);
*/

UCLASS(config = Game)
class ADynamicCreateConstraintActor : public AActor
{
	GENERATED_BODY()

public:
	ADynamicCreateConstraintActor(const FObjectInitializer& ObjectInitializer);

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
		//Collision
		//Constraint.bDisableCollision = bDisableCollision;
		Constraint.SetDisableCollision(bDisableCollision);

		switch (XLim)
		{
		//case 0: Constraint.LinearXMotion = ELinearConstraintMotion::LCM_Free; break;
		//case 1: Constraint.LinearXMotion = ELinearConstraintMotion::LCM_Limited; break;
		//case 2: Constraint.LinearXMotion = ELinearConstraintMotion::LCM_Locked; break;
		case 0: Constraint.SetLinearXMotion(ELinearConstraintMotion::LCM_Free); break;
		case 1: Constraint.SetLinearXMotion(ELinearConstraintMotion::LCM_Limited); break;
		case 2: Constraint.SetLinearXMotion(ELinearConstraintMotion::LCM_Locked); break;
		}
		switch (YLim)
		{
		//case 0: Constraint.LinearYMotion = ELinearConstraintMotion::LCM_Free; break;
		//case 1: Constraint.LinearYMotion = ELinearConstraintMotion::LCM_Limited; break;
		//case 2: Constraint.LinearYMotion = ELinearConstraintMotion::LCM_Locked; break;
		case 0: Constraint.SetLinearYMotion(ELinearConstraintMotion::LCM_Free); break;
		case 1: Constraint.SetLinearYMotion(ELinearConstraintMotion::LCM_Limited); break;
		case 2: Constraint.SetLinearYMotion(ELinearConstraintMotion::LCM_Locked); break;
		}
		switch (ZLim)
		{
		//case 0: Constraint.LinearZMotion = ELinearConstraintMotion::LCM_Free; break;
		//case 1: Constraint.LinearZMotion = ELinearConstraintMotion::LCM_Limited; break;
		//case 2: Constraint.LinearZMotion = ELinearConstraintMotion::LCM_Locked; break;
		case 0: Constraint.SetLinearZMotion(ELinearConstraintMotion::LCM_Free); break;
		case 1: Constraint.SetLinearZMotion(ELinearConstraintMotion::LCM_Limited); break;
		case 2: Constraint.SetLinearZMotion(ELinearConstraintMotion::LCM_Locked); break;
		}
		//~~~~~~~~~~

		//Constraint.LinearLimitSize = Size;
		Constraint.SetLinearLimitSize(Size);

		//if (SoftLimit) Constraint.bLinearLimitSoft = 1;
		//else Constraint.bLinearLimitSoft = 0;

		//Constraint.LinearLimitStiffness = SoftStiffness;
		//Constraint.LinearLimitDamping = SoftDampening;

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
		//case 0: Constraint.AngularSwing1Motion = EAngularConstraintMotion::ACM_Free; break;
		//case 1: Constraint.AngularSwing1Motion = EAngularConstraintMotion::ACM_Limited; break;
		//case 2: Constraint.AngularSwing1Motion = EAngularConstraintMotion::ACM_Locked; break;
		//case 0: Constraint.SetAngularSwing1Motion(EAngularConstraintMotion::ACM_Free); break;
		//case 1: Constraint.SetAngularSwing1Motion(EAngularConstraintMotion::ACM_Limited); break;
		//case 2: Constraint.SetAngularSwing1Motion(EAngularConstraintMotion::ACM_Locked); break;
		case 0: Constraint.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Free, Swing1LimitAngle); break;
		case 1: Constraint.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Limited, Swing1LimitAngle); break;
		case 2: Constraint.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, Swing1LimitAngle); break;
		}
		switch (S2Lim)
		{
		//case 0: Constraint.AngularSwing2Motion = EAngularConstraintMotion::ACM_Free; break;
		//case 1: Constraint.AngularSwing2Motion = EAngularConstraintMotion::ACM_Limited; break;
		//case 2: Constraint.AngularSwing2Motion = EAngularConstraintMotion::ACM_Locked; break;
		//case 0: Constraint.SetAngularSwing2Motion(EAngularConstraintMotion::ACM_Free); break;
		//case 1: Constraint.SetAngularSwing2Motion(EAngularConstraintMotion::ACM_Limited); break;
		//case 2: Constraint.SetAngularSwing2Motion(EAngularConstraintMotion::ACM_Locked); break;
		case 0: Constraint.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, Swing2LimitAngle); break;
		case 1: Constraint.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Limited, Swing2LimitAngle); break;
		case 2: Constraint.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, Swing2LimitAngle); break;
		}
		switch (TLim)
		{
		//case 0: Constraint.AngularTwistMotion = EAngularConstraintMotion::ACM_Free; break;
		//case 1: Constraint.AngularTwistMotion = EAngularConstraintMotion::ACM_Limited; break;
		//case 2: Constraint.AngularTwistMotion = EAngularConstraintMotion::ACM_Locked; break;
		//case 0: Constraint.SetAngularTwistMotion(EAngularConstraintMotion::ACM_Free); break;
		//case 1: Constraint.SetAngularTwistMotion(EAngularConstraintMotion::ACM_Limited); break;
		//case 2: Constraint.SetAngularTwistMotion(EAngularConstraintMotion::ACM_Locked); break;
		case 0: Constraint.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, TwistLimitAngle); break;
		case 1: Constraint.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Limited, TwistLimitAngle); break;
		case 2: Constraint.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, TwistLimitAngle); break;
		}
		//~~~~~~~~~~

		//Soft Lmit?
		//if (SoftSwingLimit) Constraint.bSwingLimitSoft = 1;
		//else Constraint.bSwingLimitSoft = 0;

		//if (SoftTwistLimit) Constraint.bTwistLimitSoft = 1;
		//else Constraint.bTwistLimitSoft = 0;

		//Limit Angles
		//Constraint.Swing1LimitAngle = Swing1LimitAngle;
		//Constraint.Swing2LimitAngle = Swing2LimitAngle;
		//Constraint.TwistLimitAngle = TwistLimitAngle;

		//Constraint.SwingLimitStiffness = SwingStiff;
		//Constraint.SwingLimitDamping = SwingDamp;
		//Constraint.TwistLimitStiffness = TwistStiff;
		//Constraint.TwistLimitDamping = TwistDamp;

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