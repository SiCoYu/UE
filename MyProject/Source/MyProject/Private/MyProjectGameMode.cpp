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
	// 最新的 ThirdPerson 资源存放文件夹又改了
	// ThirdPerson Cpp 资源加载
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	// ThirdPerson Blueprint 资源加载
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
	// 各种初始化
	EngineApi::showCursor();

	// 各种 UI 测试
	TestUI();
}

void AMyProjectGameMode::TestUI()
{
	// Test 加载 UIPack
	//g_pUIMgr->loadForm<UUIPack>(eUIPack);
	g_pUIMgr->loadForm<UUITestCanvas>(eUITestCanvas);
}