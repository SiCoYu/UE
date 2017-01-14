#pragma once

#include "GameFramework/DefaultPawn.h"
#include "MyDefaultPawnBase.generated.h"

UCLASS(config = Game)
class AMyDefaultPawnBase : public ADefaultPawn
{
	GENERATED_BODY()

public:
	AMyDefaultPawnBase(const FObjectInitializer& PCIP);
};