#pragma once

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/SkeletalMeshActor.h"
#include "Runtime/Engine/Classes/Animation/BlendSpace1D.h"
#include "Runtime/Engine/Classes/Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "PlayAnimByCppActor.generated.h"

/**
 * @ref https://aigo.iteye.com/blog/2283454
 * @ref https://aigo.iteye.com/blog/2285001
*/

class UBlendSpace1D;
class UAnimSequence;
class UStaticMeshComponent;
class UAnimMontage;

UCLASS(config = Game)
class APlayAnimByCppActor : public AActor
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* MyStaticMesh;
	float MyAnimTimer;
	FTimerHandle PauseMontageTimerHandle;

public:
	// LogCompile: Error: BlueprintReadOnly should not be used on private members
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
	UBlendSpace1D* BlendSpace;

	// LogCompile: Error: BlueprintReadOnly should not be used on private members
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
	UAnimSequence* MyAnimSequence;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
	UAnimMontage* MyMontage;

public:
	APlayAnimByCppActor(const FObjectInitializer& ObjectInitializer);

	void TestReplaceSkeletonMesh();
	void PlayBlendSpaceAnim();
	void PlayAnimSequence();
	void PlayMontage();
	void PauseMontageFunc();

	void SetAnimInstanceClass(UClass* NewClass);
};