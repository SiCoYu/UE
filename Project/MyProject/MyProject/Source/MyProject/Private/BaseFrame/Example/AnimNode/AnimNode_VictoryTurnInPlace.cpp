// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#include "MyProject.h"
#include "Animation/AnimInstanceProxy.h"	// FAnimInstanceProxy
#include "AnimNode_VictoryTurnInPlace.h"

//#include "AnimationRuntime.h"

FAnimNode_VictoryTurnInPlace::FAnimNode_VictoryTurnInPlace()
	: FAnimNode_Base()
	, TurnBlendDuration(4.f)
	, TurnSpeedModifierMAX(4.333)
	, TurnSensitivity(0.777f)
	, MoveSensitivity(25.f)
{
	WorldIsGame = false;
	BlendDurationMult = 1;
	InternalBlendDuration = TurnBlendDuration / 100;

	RangeIn = FVector2D(0, TurnSpeedModifierMAX);
	RangeOut = FVector2D(0, 1);

	ShowTurnRotationChangePerTick = false;
}

void FAnimNode_VictoryTurnInPlace::Initialize_AnyThread(const FAnimationInitializeContext & Context)
{
	//Init the Inputs
	BasePose.Initialize(Context);
	TurnPose.Initialize(Context);

	//Get the Actor Owner
	// 'FAnimationBaseContext::AnimInstance': Please use AnimInstanceProxy Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//OwningActor = Context.AnimInstance->GetSkelMeshComponent()->GetOwner();
	OwningActor = Context.AnimInstanceProxy->GetSkelMeshComponent()->GetOwner();

	//Editor or Game?
	// 'FAnimationBaseContext::AnimInstance': Please use AnimInstanceProxy Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//UWorld * TheWorld = Context.AnimInstance->GetWorld();
	//UWorld * TheWorld = Context.AnimInstanceProxy->GetWorld();
	UWorld * TheWorld = Cast<AActor>(Context.AnimInstanceProxy->GetSkelMeshComponent()->GetOuter())->GetWorld();
	if (!TheWorld) return;
	//~~~~~~~~~~~~~~~~

	WorldIsGame = (TheWorld->WorldType == EWorldType::Game);

	//~~~

	//~~~ Init the Blend ~~~
	//OurVeryOwnBlend.A = BasePose;
	//OurVeryOwnBlend.B = TurnPose;
	//OurVeryOwnBlend.Initialize(Context);
}

void FAnimNode_VictoryTurnInPlace::DetermineUseTurnPose()
{
	//Delta time
	//Context.GetDeltaTime();

	//Get Current
	CurYaw = OwningActor->GetActorRotation().Yaw;
	CurLoc = OwningActor->GetActorLocation();

	//~~~ Choose Turn Pose or Base Pose ~~~
	//Yaw Delta Amount
	TurnAmountThisTick = FMath::Abs(CurYaw - PrevYaw);
	if (TurnAmountThisTick < TurnSensitivity)
	{
		BlendingIntoTurnPose = false;
	}

	//Turning Amount is Sufficient and Movement is slow enough
	else if (FVector::DistSquared(CurLoc, PrevLoc) < MoveSensitivity)
	{
		BlendingIntoTurnPose = true;
	}

	//~~~ Save Previous ~~~
	PrevYaw = CurYaw;
	PrevLoc = CurLoc;

	//Log the Change in Rotation Per Tick
	if (ShowTurnRotationChangePerTick) UE_LOG(LogAnimation, Warning, TEXT("turn difference per tick,  %f"), TurnAmountThisTick);

	//~~~ Calc Blend Mult ~~~

	//In case this gets modified during game time
	RangeIn.Y = TurnSpeedModifierMAX;

	//Mapped Range
	// FMath::GetMappedRangeValue': GetMappedRangeValue is deprecated. Use GetMappedRangeValueClamped instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//BlendDurationMult = FMath::GetMappedRangeValue(RangeIn, RangeOut, TurnAmountThisTick);
	BlendDurationMult = FMath::GetMappedRangeValueClamped(RangeIn, RangeOut, TurnAmountThisTick);
}

void FAnimNode_VictoryTurnInPlace::UpdateBlendAlpha()
{
	if (BlendingIntoTurnPose)
	{
		if (BlendAlpha >= 1) BlendAlpha = 1;
		else BlendAlpha += InternalBlendDuration * BlendDurationMult; //modify blend-in by speed of turning
	}

	//Blending out
	else
	{
		if (BlendAlpha <= 0) BlendAlpha = 0;
		else BlendAlpha -= InternalBlendDuration;
	}
}

void FAnimNode_VictoryTurnInPlace::Update_AnyThread(const FAnimationUpdateContext & Context)
{
	//EDITOR
	//Editor mode? just use the base pose
	if (!WorldIsGame)
	{
		BlendAlpha = 0;
	}

	//GAME
	//Actually in Game so the Owner Instance Should Exist
	else
	{
		//Try Again if not found
		// 'FAnimationBaseContext::AnimInstance': Please use AnimInstanceProxy Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//if (!OwningActor) OwningActor = Context.AnimInstance->GetSkelMeshComponent()->GetOwner();
		if (!OwningActor) OwningActor = Context.AnimInstanceProxy->GetSkelMeshComponent()->GetOwner();

		//Not found
		if (!OwningActor)
		{
			UE_LOG(LogAnimation, Warning, TEXT("FAnimNode_VictoryTurnInPlace::Update() Owning Actor was not found"));
			return;
			//~~~~~~~~~~~~~~~~~~~
		}

		//~~~ Determine Use Turn Pose ~~~
		DetermineUseTurnPose();

		//~~~ Calc Blend Alpha ~~~
		UpdateBlendAlpha();
	}

	//~~~ Do Updates ~~~

	//At end of Blend, only evaluate 1, save resources
	//**************************************************************************
	// FPoseLinkBase::Update Active Pose - this is what makes the glowing line thing happen and animations loop
	//**************************************************************************
	if (BlendAlpha >= 1) TurnPose.Update(Context);
	else if (BlendAlpha <= 0) BasePose.Update(Context);

	//Currently Blending
	else
	{
		//Blend node below handles this now
		//BasePose.Update(Context);
		//TurnPose.Update(Context);

		//~~~ Update the Blend ~~~
		//OurVeryOwnBlend.Alpha = BlendAlpha;
		//OurVeryOwnBlend.Update(Context);
	}

	//***************************************
	// Evaluate Graph, see AnimNode_Base, AnimNodeBase.h
	// error C2065: 'EvaluateGraphExposedInputs': undeclared identifier
	//EvaluateGraphExposedInputs.Execute(Context);
	this->GetEvaluateGraphExposedInputs().Execute(Context);
	//***************************************
}

void FAnimNode_VictoryTurnInPlace::Evaluate_AnyThread(FPoseContext & Output)
{
	//~~~ Fully In Base Pose ~~~
	if (BlendAlpha <= 0) BasePose.Evaluate(Output);

	//~~~ Fully In Turn Pose ~~~
	else if (BlendAlpha >= 1) TurnPose.Evaluate(Output);

	//~~~ Currently Blending ~~~
	else
	{
		//OurVeryOwnBlend.Evaluate(Output);
	}
}