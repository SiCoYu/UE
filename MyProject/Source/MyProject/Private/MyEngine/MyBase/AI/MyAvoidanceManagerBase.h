#pragma once

#include "AI/Navigation/AvoidanceManager.h"		// UAvoidanceManager
#include "MyAvoidanceManagerBase.generated.h"

UCLASS(config = Engine, Blueprintable)
class UMyAvoidanceManagerBase : public UAvoidanceManager
{
	GENERATED_UCLASS_BODY()
};