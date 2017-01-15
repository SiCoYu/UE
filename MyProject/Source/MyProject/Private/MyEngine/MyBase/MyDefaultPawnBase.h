#pragma once

#include "GameFramework/Pawn.h"
#include "MyDefaultPawnBase.generated.h"

UCLASS(config = Game)
class AMyDefaultPawnBase : public APawn
{
	GENERATED_BODY()

public:
	AMyDefaultPawnBase(const FObjectInitializer& PCIP);
};
