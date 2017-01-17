#pragma once

#include "MyCharacterMovementComponentBase.h"
#include "MyTPCharacterMovementComponent.generated.h"

UCLASS()
class UMyTPCharacterMovementComponent : public MyCharacterMovementComponentBase
{
	GENERATED_UCLASS_BODY()

	virtual float GetMaxSpeed() const override;
};

