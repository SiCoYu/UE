// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyProject.h"
#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "GameFramework/HUD.h"

AMyProjectGameMode::AMyProjectGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> HUBBPClass(TEXT("/Game/Blueprints/HUB"));
	if (HUBBPClass.Class != NULL)
	{
		HUDClass = HUBBPClass.Class;
	}
}
