// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyProject.h"
#include "Animation/AnimNodeBase.h"	// FAnimNode_Base
#include "AnimNode_NameOfYourNode.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Animation_Nodes,_Code_for_How_to_Create_Your_Own
 */

// UE4 4.17
// Issue with new stricter UHT and USTRUCTs
// https://answers.unrealengine.com/questions/675941/issue-with-new-stricter-uht-and-ustructs.html
//USTRUCT()
USTRUCT(BlueprintInternalUseOnly)
struct FAnimNode_NameOfYourNode : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	//FPoseLink - this can be any combination 
	//of other nodes, not just animation sequences
	//	so you could have an blend space leading into 
	//a layer blend per bone to just use the arm
	//	and then pass that into the PoseLink

	/** Base Pose - This Can Be Entire Anim Graph Up To This Point, or Any Combination of Other Nodes*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FPoseLink BasePose;

	/** Other Pose! - This Can Be Entire Anim Graph Up To This Point, or Any Combination of Other Nodes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FPoseLink OtherPose;

	/** Sample Property That Will Show Up as a Pin */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	float SampleFloat;

	// FAnimNode_Base interface
public:

	// FAnimNode_Base interface
	// 'EMIT_DEPRECATED_WARNING_MESSAGE': unknown override specifier
	//virtual void Initialize(const FAnimationInitializeContext& Context) OVERRIDE;
	//virtual void CacheBones(const FAnimationCacheBonesContext & Context) OVERRIDE;
	//virtual void Update(const FAnimationUpdateContext & Context) OVERRIDE;
	//virtual void Evaluate(FPoseContext& Output) OVERRIDE;
	virtual void Initialize(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones(const FAnimationCacheBonesContext & Context) override;
	virtual void Update(const FAnimationUpdateContext & Context) override;
	virtual void Evaluate(FPoseContext& Output) override;
	// End of FAnimNode_Base interface

	// Constructor 
public:

	FAnimNode_NameOfYourNode();

protected:
	bool WorldIsGame;
	AActor* OwningActor;
};