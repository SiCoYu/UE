#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacterMovementComponentBase.generated.h"

UCLASS()
class UMyCharacterMovementComponentBase : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()

	virtual float GetMaxSpeed() const override;
};