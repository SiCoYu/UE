#pragma once

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/SkeletalMeshActor.h"
#include "PlayAnimByCppActor.generated.h"

/**
 * @ref https://aigo.iteye.com/blog/2283454
 * @ref https://aigo.iteye.com/blog/2285001
*/

UCLASS(config = Game)
class APlayAnimByCppActor : public AActor
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* MyStaticMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
		UBlendSpace1D* BlendSpace;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims");
	UAnimSequence* MyAnimSequence;

public:
	APlayAnimByCppActor(const FObjectInitializer& ObjectInitializer);

	void TestReplaceSkeletonMesh();
	void PlayBlendSpaceAnim();
	void PlayAnimSequence();
	void PlayMontage();

	void SetAnimInstanceClass(UClass* NewClass);
};