#pragma once

#include "AI/Navigation/AvoidanceManager.h"		// UAvoidanceManager
#include "MyAvoidanceManager.generated.h"

UCLASS(config = Engine, Blueprintable)
class UMyAvoidanceManager : public UAvoidanceManager
{
	GENERATED_BODY()
};