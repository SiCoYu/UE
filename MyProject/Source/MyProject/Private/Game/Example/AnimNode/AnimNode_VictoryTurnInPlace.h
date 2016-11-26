#pragma once

#include "MyProject.h"
#include "AnimNode_VictoryTurnInPlace.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Animation_Node,_Entire_Source_for_a_Turn_In_Place_Node
 * @brief Please note the use of WorldIsGame.

In the editor, there is no instanced version of the Character, so I do not run that part of the code.

Here is how you can determine if your node is running in the Editor preview or in the actual game!

WorldIsGame = (TheWorld->WorldType == EWorldType::Game);
 */

USTRUCT()
struct FAnimNode_VictoryTurnInPlace : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	/** Base Pose*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FPoseLink BasePose;

	/** Turning In Place! */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FPoseLink TurnPose;

	/** How Quickly to Blend In/Out of Turn Pose */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	float TurnBlendDuration;

	/** What Amount of Turn Per Tick Qualifies for Maximum Turn Blending? Anything less per tick will result in slower Turn Blending. Result: If player turns slowly, the turn blend blends in slowly, and ramps up smoothly to max turn blend as player turns faster. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	float TurnSpeedModifierMAX;

	/** The Lower This Number The Faster The Turn In Place Anim Will Activate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	float TurnSensitivity;

	/** The Lower This Number The Faster The Turn In Place Anim Will Activate */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	float MoveSensitivity;

	/** Seeing this in the log can help you decided what TurnSpeedModifierMAX to use  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Logs)
	float ShowTurnRotationChangePerTick;

	// FAnimNode_Base interface
public:

	// FAnimNode_Base interface
	virtual void Initialize(const FAnimationInitializeContext& Context) 	OVERRIDE;
	virtual void Update(const FAnimationUpdateContext & Context) 		OVERRIDE;
	virtual void Evaluate(FPoseContext& Output) 							OVERRIDE;
	// End of FAnimNode_Base interface

	//~~~ Constructor ~~~
public:

	FAnimNode_VictoryTurnInPlace();

	//Functions
protected:
	void DetermineUseTurnPose();
	void UpdateBlendAlpha();

protected:

	//Our very own Blend node, yay! (makes this all super clear)
	FAnimationNode_TwoWayBlend OurVeryOwnBlend;

	AActor * OwningActor;
	FVector PrevLoc;
	FVector CurLoc;
	float PrevYaw;
	float CurYaw;
	float TurnAmountThisTick;
	bool WorldIsGame;

	//~~~ Blending ~~~
	float BlendDurationMult; //blend slower if moving slower
	float InternalBlendDuration; //divided the input by 100 just cause it looks better that way
	float BlendAlpha;
	bool BlendingIntoTurnPose; //false = blending out of

	FVector2D RangeIn;
	FVector2D RangeOut;
};