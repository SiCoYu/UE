#include "MyProject.h"
#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "GameFramework/HUD.h"
#include "UI/MyHUD.h"
#include "Common.h"
#include "UIFormID.h"
#include "UIPack.h"
#include "UITestCanvas.h"

AMyProjectGameMode::AMyProjectGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	// ���µ� ThirdPerson ��Դ����ļ����ָ���
	// ThirdPerson Cpp ��Դ����
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	// ThirdPerson Blueprint ��Դ����
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
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
	EngineApi::showCursor();

	// ���� UI ����
	TestUI();
}

void AMyProjectGameMode::TestUI()
{
	// Test ���� UIPack
	//g_pUIMgr->loadForm<UUIPack>(eUIPack);
	g_pUIMgr->loadForm<UUITestCanvas>(eUITestCanvas);
}