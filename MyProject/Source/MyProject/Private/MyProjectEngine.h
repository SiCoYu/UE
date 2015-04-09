#pragma once

// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ShooterEngine.generated.h"

UCLASS()
class UMyProjectEngine : public UGameEngine
{
	GENERATED_UCLASS_BODY()

	/* Hook up specific callbacks */
	virtual void Init(IEngineLoop* InEngineLoop);
};