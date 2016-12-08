#pragma once

#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
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
	DynamicCreateConstraintActor(const FObjectInitializer& ObjectInitializer);

	void CreateNewPhysicsConstraintBetween(AStaticMeshActor* RootSMA, AStaticMeshActor* TargetSMA)

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
		Constraint.bDisableCollision = bDisableCollision;

		switch (XLim)
		{
		case 0: Constraint.LinearXMotion = ELinearConstraintMotion::LCM_Free; break;
		case 1: Constraint.LinearXMotion = ELinearConstraintMotion::LCM_Limited; break;
		case 2: Constraint.LinearXMotion = ELinearConstraintMotion::LCM_Locked; break;
		}
		switch (YLim)
		{
		case 0: Constraint.LinearYMotion = ELinearConstraintMotion::LCM_Free; break;
		case 1: Constraint.LinearYMotion = ELinearConstraintMotion::LCM_Limited; break;
		case 2: Constraint.LinearYMotion = ELinearConstraintMotion::LCM_Locked; break;
		}
		switch (ZLim)
		{
		case 0: Constraint.LinearZMotion = ELinearConstraintMotion::LCM_Free; break;
		case 1: Constraint.LinearZMotion = ELinearConstraintMotion::LCM_Limited; break;
		case 2: Constraint.LinearZMotion = ELinearConstraintMotion::LCM_Locked; break;
		}
		//~~~~~~~~~~

		Constraint.LinearLimitSize = Size;

		if (SoftLimit) Constraint.bLinearLimitSoft = 1;
		else Constraint.bLinearLimitSoft = 0;

		Constraint.LinearLimitStiffness = SoftStiffness;
		Constraint.LinearLimitDamping = SoftDampening;
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
		case 0: Constraint.AngularSwing1Motion = EAngularConstraintMotion::ACM_Free; break;
		case 1: Constraint.AngularSwing1Motion = EAngularConstraintMotion::ACM_Limited; break;
		case 2: Constraint.AngularSwing1Motion = EAngularConstraintMotion::ACM_Locked; break;
		}
		switch (S2Lim)
		{
		case 0: Constraint.AngularSwing2Motion = EAngularConstraintMotion::ACM_Free; break;
		case 1: Constraint.AngularSwing2Motion = EAngularConstraintMotion::ACM_Limited; break;
		case 2: Constraint.AngularSwing2Motion = EAngularConstraintMotion::ACM_Locked; break;
		}
		switch (TLim)
		{
		case 0: Constraint.AngularTwistMotion = EAngularConstraintMotion::ACM_Free; break;
		case 1: Constraint.AngularTwistMotion = EAngularConstraintMotion::ACM_Limited; break;
		case 2: Constraint.AngularTwistMotion = EAngularConstraintMotion::ACM_Locked; break;
		}
		//~~~~~~~~~~

		//Soft Lmit?
		if (SoftSwingLimit) Constraint.bSwingLimitSoft = 1;
		else Constraint.bSwingLimitSoft = 0;

		if (SoftTwistLimit) Constraint.bTwistLimitSoft = 1;
		else Constraint.bTwistLimitSoft = 0;

		//Limit Angles
		Constraint.Swing1LimitAngle = Swing1LimitAngle;
		Constraint.Swing2LimitAngle = Swing2LimitAngle;
		Constraint.TwistLimitAngle = TwistLimitAngle;

		Constraint.SwingLimitStiffness = SwingStiff;
		Constraint.SwingLimitDamping = SwingDamp;
		Constraint.TwistLimitStiffness = TwistStiff;
		Constraint.TwistLimitDamping = TwistDamp;
	}
};