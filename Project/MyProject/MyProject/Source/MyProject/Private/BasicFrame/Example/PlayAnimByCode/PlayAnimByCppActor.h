#pragma once

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/SkeletalMeshActor.h"
#include "Runtime/Engine/Classes/Animation/BlendSpace1D.h"
#include "Runtime/Engine/Classes/Animation/AnimSequence.h"
#include "PlayAnimByCppActor.generated.h"

/**
 * @ref https://aigo.iteye.com/blog/2283454
 * @ref https://aigo.iteye.com/blog/2285001
*/

class UBlendSpace1D;
class UAnimSequence;
class UStaticMeshComponent;

UCLASS(config = Game)
class APlayAnimByCppActor : public AActor
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* MyStaticMesh;

public:
	// LogCompile: Error: BlueprintReadOnly should not be used on private members
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
	UBlendSpace1D* BlendSpace;

	// LogCompile: Error: BlueprintReadOnly should not be used on private members
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
	UAnimSequence* MyAnimSequence;

public:
	APlayAnimByCppActor(const FObjectInitializer& ObjectInitializer);

	void TestReplaceSkeletonMesh();
	void PlayBlendSpaceAnim();
	void PlayAnimSequence();
	void PlayMontage();

	void SetAnimInstanceClass(UClass* NewClass);
};