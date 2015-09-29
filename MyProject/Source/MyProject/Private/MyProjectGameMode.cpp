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
	// ���µ� ThirdPerson ��Դ����ļ����и���
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
	// ���ֳ�ʼ��
	Ctx::getSingletonPtr()->getEngineApi()->showCursor();
	Ctx::getSingletonPtr()->getUIMgr()->loadForm<UUIPack>(eUIPack);
}