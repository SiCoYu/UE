// Created by Chance_07 2014
#pragma once

#include "MyProject.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_TranslateWith.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Animation_Node,_Translate_With_Complete_Source_Code_and_Instructions
 */

// UE4 4.17
// Issue with new stricter UHT and USTRUCTs
// https://answers.unrealengine.com/questions/675941/issue-with-new-stricter-uht-and-ustructs.html
//USTRUCT()
USTRUCT(BlueprintInternalUseOnly)
struct FAnimNode_TranslateWith : public  FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	/** Input link(Base Pose) **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FComponentSpacePoseLink ComponentPose;

	// LogCompile: Error: Type 'FBoneReference' is not supported by blueprint. AnimNode_TranslateWith.TargetBone
	/** Name of bone to control **/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl)
	FBoneReference TargetBone;

	// LogCompile: Error: Type 'FBoneReference' is not supported by blueprint. AnimNode_TranslateWith.SourceBone
	/** Source Bone Name to get transform from **/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl)
	FBoneReference SourceBone;

	/** This is typically the FORWARD Axis, and is false by default **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AxisLock, meta = (PinHiddenByDefault))
	bool bUpdateX;

	/** This is typically the SIDE-TO-SIDE Axis, and is false by default **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AxisLock, meta = (PinHiddenByDefault))
	bool bUpdateY;

	/** This is typically the UP Axis, and is true by default **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AxisLock, meta = (PinHiddenByDefault))
	bool bUpdateZ;

	/** Target Location in world space if LookAtBone is empty */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl)
	FVector AddtoOffset;

	/** Controls how much of the translation is blended to the target, default is 1 **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl, meta = (PinShownByDefault))
	float BlendWeight;
public:
	FAnimNode_TranslateWith();
public:
	// FAnimNode_Base interface
	//virtual void Initialize(const FAnimationInitializeContext& Context) OVERRIDE;
	//virtual void CacheBones(const FAnimationCacheBonesContext & Context)  OVERRIDE;
	//virtual void Update(const FAnimationUpdateContext& Context) OVERRIDE;
	//virtual void EvaluateComponentSpace(FComponentSpacePoseContext& Output) OVERRIDE;
	// UE4 4.17: warning C4996: 'FAnimNode_Base::Initialize': Please use Initialize_AnyThread instead Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//virtual void Initialize(const FAnimationInitializeContext& Context) override;
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	// UE4 4.17: warning C4996: 'FAnimNode_Base::CacheBones': Please use CacheBones_AnyThread instead Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//virtual void CacheBones(const FAnimationCacheBonesContext & Context)  override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext & Context)  override;
	// UE4 4.17: warning C4996: 'FAnimNode_Base::Update': Please use Update_AnyThread instead Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//virtual void Update(const FAnimationUpdateContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	// UE4 4.17: warning C4996: 'FAnimNode_Base::EvaluateComponentSpace': Please use EvaluateComponentSpace_AnyThread instead Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//virtual void EvaluateComponentSpace(FComponentSpacePoseContext& Output) override;
	virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output) override;
	// End of FAnimNode_RCAnimNode interface
protected:
	// initialize any bone references you have
	virtual void InitializeBoneReferences(const FBoneContainer & RequiredBones);
	// return true if it is valid to Evaluate
	virtual bool IsValidToEvaluate(const USkeleton * Skeleton, const FBoneContainer & RequiredBones);
	// Evaluate the new component-space transforms for the affected bones.
	//virtual void EvaluateBoneTransforms(USkeletalMeshComponent* SkelComp, const FBoneContainer & RequiredBones, FA2CSPose& MeshBases, TArray<FBoneTransform>& OutBoneTransforms);// {}
	virtual void EvaluateBoneTransforms(USkeletalMeshComponent* SkelComp, const FBoneContainer & RequiredBones, FCSPose<FCompactPose>& MeshBases, TArray<FBoneTransform>& OutBoneTransforms);// {}
private:
	FVector ModTargetLocationInCompSpace;
	FVector CurrentAddedOffset;
	FVector JointOffset;
};