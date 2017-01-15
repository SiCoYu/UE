#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawnBase.generated.h"

UCLASS(config = Game)
class AMyPawnBase : public APawn
{
	GENERATED_BODY()

public:
	AMyPawnBase();
};
