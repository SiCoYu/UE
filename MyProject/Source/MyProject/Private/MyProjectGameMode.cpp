// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyProject.h"
#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "GameFramework/HUD.h"
#include "UI/MyHUD.h"
#include "Common.h"
#include "UIFormID.h"
#include "UIPack.h"

AMyProjectGameMode::AMyProjectGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	// 最新的 ThirdPerson 资源存放文件夹有改了
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//static ConstructorHelpers::FClassFinder<AHUD> HUBBPClass(TEXT("/Game/Blueprints/HUB"));
	//if (HUBBPClass.Class != NULL)
	//{
		//HUDClass = HUBBPClass.Class;
		HUDClass = AMyHUD::StaticClass();
	//}
}

void AMyProjectGameMode::StartPlay()
{
	Super::StartPlay();
	// 各种初始化
	Ctx::getSingletonPtr()->getEngineApi()->showCursor();
	Ctx::getSingletonPtr()->getUIMgr()->loadForm<UUIPack>(eUIPack);
}