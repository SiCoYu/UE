// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
ShooterEngine.cpp: ShooterEngine c++ code.
=============================================================================*/

#include "MyProject.h"

UMyProjectEngine::UShooterEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMyProjectEngine::Init(IEngineLoop* InEngineLoop)
{
	// Note: Lots of important things happen in Super::Init(), including spawning the player pawn in-game and
	// creating the renderer.
	Super::Init(InEngineLoop);
}