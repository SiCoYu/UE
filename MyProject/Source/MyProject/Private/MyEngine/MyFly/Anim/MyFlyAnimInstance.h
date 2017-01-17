#pragma once

#include "Animation/AnimInstance.h"
#include "Math/Rotator.h"

#include "MyAnimInstanceBase"
#include "MyFlyAnimInstance.generated.h"

UCLASS(config = Game)
class UMyFlyAnimInstance : public UMyAnimInstanceBase
{
	GENERATED_UCLASS_BODY()

//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
//	FRotator NeckSpring;
//
//public:
//	void testA();
//
//public:
//	APawn * OwningPawn;
//
//	/** Is Moving */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
//	bool IsMoving;
//
//	//init and tick
//public:
//	virtual void NativeInitializeAnimation() override;
//	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
};