#pragma once

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/SkeletalMeshActor.h"
#include "Runtime/Engine/Classes/Animation/BlendSpace1D.h"
#include "Runtime/Engine/Classes/Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "CreateComponentByCodeActor.generated.h"

/**
 * @ref https://aigo.iteye.com/blog/2283454
 * @ref https://aigo.iteye.com/blog/2285001
*/

class UBlendSpace1D;
class UAnimSequence;
class UStaticMeshComponent;
class UAnimMontage;
class UBehaviorTreeComponent;
class USkeletalMeshComponent;

UCLASS(config = Game)
class ACreateComponentByCodeActor : public AActor
{
	GENERATED_BODY()

protected:
	USkeletalMeshComponent* mMeshCompPtr;
	UBehaviorTreeComponent* mBehaviorTreeCompPtr;

public:
	// https://blog.csdn.net/iuoon/article/details/75208749
	void createSkeletalMeshComponent();

	void createBehaviorTreeComponent();
};