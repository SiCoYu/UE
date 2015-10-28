#pragma once

#include "Animation/AnimInstance.h"
#include "Math/Rotator.h"

#include "MyAnimInstance.generated.h"

UCLASS(config = Game)
class UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	FRotator NeckSpring;

public:
	void testA();
};