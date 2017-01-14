#pragma once

#include "UObject/Object.h"
#include "MyBluePrintBase.generated.h"

UCLASS(config = Game)
class UMyBluePrintBase : public UObject
{
	GENERATED_BODY()

public:
	UMyBluePrintBase(const FObjectInitializer& PCIP);
};