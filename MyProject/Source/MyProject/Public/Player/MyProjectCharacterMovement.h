#pragma once
#include "MyProjectCharacterMovement.generated.h"

UCLASS()
class UMyProjectCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()

	virtual float GetMaxSpeed() const override;
};

