#pragma once

#include "GameFramework/FloatingPawnMovement.h"
#include "MyDefaultMovementComponentBase.generated.h"

UCLASS(config = Game)
class UMyDefaultMovementComponentBase : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:
	UMyDefaultMovementComponentBase(const FObjectInitializer& PCIP);
};