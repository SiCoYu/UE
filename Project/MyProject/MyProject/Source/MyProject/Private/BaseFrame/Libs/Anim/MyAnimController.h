#pragma once

#include "PlatformDefine.h"

class AActor;
class UMyAnimInstanceBase;
class USkeletalMeshComponent;
class USkeletalMesh;
class UMesh;
class USkeleton;

MY_BEGIN_NAMESPACE(MyNS)

class MyAnimController
{
protected:
	AActor* mActorPtr;
	UMyAnimInstanceBase* mAnimInstancePtr;
	USkeletalMeshComponent* mMeshComp;
	USkeletalMesh* mSkeletalMesh;
	USkeleton* mSkeleton;
	UMesh* mMesh;

public:
	void init();
	void dispose();

	void setActor(AActor* actor);
	/**
	 * @ref https://answers.unrealengine.com/questions/569609/view.html
	 */
	void setAnimBlueprint_Test();
};

MY_END_NAMESPACE