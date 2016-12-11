#pragma once

#include "MyEngine.generated.h"

UCLASS()
class UMyEngine : public UGameEngine
{
	GENERATED_UCLASS_BODY()

	/* Hook up specific callbacks */
	virtual void Init(IEngineLoop* InEngineLoop);
};