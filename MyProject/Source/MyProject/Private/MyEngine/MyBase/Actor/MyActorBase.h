#pragma once

#include "GameFramework/Pawn.h"
#include "MyActorBase.generated.h"

UCLASS(config=Game)
class AMyActorBase : public APawn
{
	GENERATED_BODY()

public:
	AMyActorBase();
};
