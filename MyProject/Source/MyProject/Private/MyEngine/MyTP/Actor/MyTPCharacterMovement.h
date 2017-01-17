#pragma once
#include "MyCharacterMovement.generated.h"

UCLASS()
class UMyCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()

	virtual float GetMaxSpeed() const override;
};

