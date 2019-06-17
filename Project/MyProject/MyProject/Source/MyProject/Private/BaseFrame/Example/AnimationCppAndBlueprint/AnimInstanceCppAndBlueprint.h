#pragma once

#include "MyProject.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceCppAndBlueprint.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Animation_Blueprint,_Implement_Custom_C%2B%2B_Logic_Via_Tick_Updates
 * @brief Cpp 和 Blueprint 共同驱动动画系统
 * @brief File -- Reparent Blueprint 
 */

UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class UAnimInstanceCppAndBlueprint : public UAnimInstance
{
	GENERATED_BODY()
public:
	/** Is Moving */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	bool IsMoving;

	//init and tick
public:
	APawn * OwningPawn;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
};