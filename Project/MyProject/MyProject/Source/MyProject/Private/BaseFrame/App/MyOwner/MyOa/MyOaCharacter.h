#pragma once

#include "MyCharacterBase.h"
#include "MyOaCharacter.generated.h"

UCLASS()
class AMyOaCharacter : public AMyCharacterBase
{
	GENERATED_BODY()

public:
	AMyOaCharacter(const FObjectInitializer& ObjectInitializer);
};