#pragma once

#include "MyProjectEngine.generated.h"

UCLASS()
class UMyProjectEngine : public UGameEngine
{
	GENERATED_UCLASS_BODY()

	/* Hook up specific callbacks */
	virtual void Init(IEngineLoop* InEngineLoop);
};