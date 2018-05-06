#include "MyProject.h"
#include "MyFlyPlayerController.h"
#include "EngineApi.h"
#include "MyFunctionLibrary.h"
#include "Net/UnrealNetwork.h"	// DOREPLIFETIME
#include "MyFlowerActor.h"	// AMyFlowerActor
#include "Blueprint/UserWidget.h"	// UUserWidget
#include "MyFlyPlayerCameraManager.h"
#include "Common.h"
#include "UiTestCanvas.h"	// UUiTestCanvas

AMyFlyPlayerController::AMyFlyPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* Initialize The Values */
	//PawnToUseA = NULL;
	//PawnToUseB = NULL;

	/* Make sure the PawnClass is Replicated */
	this->bReplicates = true;

	this->PlayerCameraManagerClass = AMyFlyPlayerCameraManager::StaticClass();
}

//void AMyPlayerController::BeginPlay()
//{
//	Super::BeginPlay();
//
//	BeginPlay_PawnClass();
//
//	BeginPlay_UMGWidgets();
//
//	// 各种初始化
//	//EngineApi::showCursor();
//
//	// 各种 UI 测试
//	//TestUI();
//
//	GEngineData->setMainPlayerController(this);
//
//	// 逻辑开始运行
//	//GCtx->beginPlay();
//}
//
//void AMyPlayerController::ReceivedPlayer()
//{
//	Super::ReceivedPlayer();
//
//	// 赋值控制 Player ，逻辑开始运行
//	//GCtx->beginPlay();
//}
//
//void AMyPlayerController::TestUI()
//{
//	// Test 加载 UIPack
//	//GUiMgr->loadForm<UUiPack>(eUiPack);
//	GUiMgr->loadForm<UUiTestCanvas>(eUiTestCanvas);
//}
//
//void AMyPlayerController::BeginPlay_PawnClass()
//{
//	DeterminePawnClass();
//}
//
//// Pawn Class
//void AMyPlayerController::DeterminePawnClass_Implementation()
//{
//	if (IsLocalController()) //Only Do This Locally (NOT Client-Only, since Server wants this too!)
//	{
//		/* Load Text File Into String Array */
//		TArray<FString> TextStrings;
//		TextStrings.Add("PawnA");
//		const FString FilePath = FPaths::GameDir() + "Textfiles/PlayerSettings.txt";
//
//		/* Use PawnA if the Text File tells us to */
//		if (TextStrings[0] == "PawnA")
//		{
//			ServerSetPawn(PawnToUseA);
//			return;
//		}
//
//		/* Otherwise, Use PawnB :) */
//		ServerSetPawn(PawnToUseB);
//
//		return;
//	}
//}
//
//bool AMyPlayerController::ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass)
//{
//	return true;
//}
//
//void AMyPlayerController::ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass)
//{
//	MyPawnClass = InPawnClass;
//
//	/* Just in case we didn't get the PawnClass on the Server in time... */
//	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
//}
//
//// Replication
//void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	DOREPLIFETIME(AMyPlayerController, MyPawnClass);
//}
//
//bool AMyPlayerController::IsActorWithinTheBoundsOfStreamedInLeve()
//{
//	bool ret = false;
//	//Get the Currently Streamed Levels
//	const TArray<ULevelStreaming*>& StreamedLevels = GetWorld()->StreamingLevels;
//
//	for (const ULevelStreaming* EachLevelStreaming : StreamedLevels)
//	{
//		if (!EachLevelStreaming)
//		{
//			continue;
//		}
//
//		ULevel* EachLevel = EachLevelStreaming->GetLoadedLevel();
//
//		//Is This Level Valid and Visible?
//		if (!EachLevel || !EachLevel->bIsVisible)
//		{
//			continue;
//		}
//
//		//Print Name of current Level Streaming to know which level the unit is in!
//		ClientMessage(EachLevelStreaming->GetWorldAssetPackageName());
//
//		//Is the Player Location Within this Level's Bounds
//		if (ALevelBounds::CalculateLevelBounds(EachLevel).IsInside(GetPawn()->GetActorLocation()))
//		{
//			ClientMessage("Yes Player Is Within This Level");
//			ret = true;
//		}
//	}
//
//	return ret;
//}
//
//void AMyPlayerController::TauntTimer()
//{
//
//}
//
//void AMyPlayerController::ServerTaunt_Implementation()
//{
//	// Only allow Taunt its been awhile since we last tried to commit Taunt.
//	// TIMEXXX macros from https://wiki.unrealengine.com/Time_Macros
//	if (TIMESINCE(LastTauntTime) > 5.0)
//	{
//		LastTauntTime = TIMENOW;
//		// Don't commit Taunt if a Taunt attempt is already pending.
//		if (!ISTIMERACTIVE(TimerHandle_Taunt))
//		{
//			// Delay the Taunt attempt a random amount to prevent trolling.
//			SETTIMERH(TimerHandle_Taunt, AMyPlayerController::TauntTimer, FMath::FRandRange(1.5f, 3.0f), false);
//		}
//	}
//}
//
//void AMyPlayerController::ExampleUsageOne()
//{
//	//In player controller class
//
//	//location the PC is focused on
//	const FVector Start = GetFocalLocation();
//
//	//256 units in facing direction of PC (256 units in front of the camera)
//	const FVector End = Start + GetControlRotation().Vector() * 256;
//
//	//The trace data is stored here
//	FHitResult HitData(ForceInit);
//
//	//If Trace Hits anything
//	if (UMyFunctionLibrary::Trace(GetWorld(), GetPawn(), Start, End, HitData))
//	{
//		//Print out the name of the traced actor
//		if (HitData.GetActor())
//		{
//			ClientMessage(HitData.GetActor()->GetName());
//
//			//Print out distance from start of trace to impact point
//			ClientMessage("Trace Distance: " + FString::SanitizeFloat(HitData.Distance));
//		}
//	}
//}
//
//void AMyPlayerController::ExampleUsageTwo()
//{
//	//In player controller class
//
//	//location the PC is focused on
//	const FVector Start = GetFocalLocation();
//
//	//2000 units in facing direction of PC (in front of the camera)
//	const FVector End = Start + GetControlRotation().Vector() * 2000;
//
//	//The trace data is stored here
//	FHitResult HitData(ForceInit);
//
//	//If Trace Hits anything (ignore the controlled pawn)
//	if (UMyFunctionLibrary::Trace(GetWorld(), GetPawn(), Start, End, HitData) && HitData.GetActor())
//	{
//		ClientMessage(HitData.GetActor()->GetName());
//
//		//Print out the distance from the trace start to the impact point!
//		ClientMessage("Distance from Trace Start to Impact: " + FString::SanitizeFloat(HitData.Distance));
//	}
//}
//
//void AMyPlayerController::ExampleUsageThree()
//{
//	//The trace data is stored here
//	FHitResult HitData(ForceInit);
//
//	//Actors to Ignore
//	//  Ignore all AFlowers
//	TArray<AActor*> ActorsToIgnore;
//	for (TObjectIterator<AMyFlowerActor> It; It; ++It)
//	{
//		ActorsToIgnore.Add(*It);
//	}
//
//	//Ignore the player character too!
//	ActorsToIgnore.Add(GetPawn());
//
//	//location the PC is focused on
//	const FVector Start = GetFocalLocation();
//
//	//2000 units in facing direction of PC (in front of the camera)
//	const FVector End = Start + GetControlRotation().Vector() * 2000;
//
//	//If Trace Hits anything
//	//if (UMyFunctionLibrary::Trace(GetWorld(), GetPawn(), Start, End, ActorsToIgnore))
//	if (UMyFunctionLibrary::Trace(GetWorld(), ActorsToIgnore, Start, End, HitData))
//	{
//		//Print out the name of the traced actor
//		if (HitData.GetActor())
//		{
//			ClientMessage(HitData.GetActor()->GetName());
//
//			//Print out distance from start of trace to impact point
//			ClientMessage("Trace Distance: " + FString::SanitizeFloat(HitData.Distance));
//		}
//	}
//}
//
//void AMyPlayerController::ExampleUsageFour()
//{
//	//In player controller class
//
//	ACharacter* CharacterToTrace = nullptr;//set to some character
//
//	if (!CharacterToTrace) return;
//	if (!CharacterToTrace->IsValidLowLevel()) return;
//	//~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//	//location the PC is focused on
//	const FVector Start = GetFocalLocation();
//
//	//256 units in facing direction of PC (256 units in front of the camera)
//	const FVector End = Start + GetControlRotation().Vector() * 256;
//
//	//The trace data is stored here
//	FHitResult HitData(ForceInit);
//
//	//If Trace Hits any part of the Mesh of the Character To Trace
//	//if (UMyFunctionLibrary::Trace(CharacterToTrace->GetMesh(), Start, End, HitData))
//	if (UMyFunctionLibrary::TraceComponent(CharacterToTrace->GetMesh(), Start, End, HitData))
//	{
//		//Print out the location of the impact on the Character's Mesh
//		ClientMessage(HitData.ImpactPoint.ToString());
//
//		//Print out distance from start of trace to impact point
//		ClientMessage("Trace Distance: " + FString::SanitizeFloat(HitData.Distance));
//	}
//}
//
//void AMyPlayerController::BeginPlay_UMGWidgets()
//{
//	// https://wiki.unrealengine.com/UMG,_Referencing_UMG_Widgets_in_Code
//	if (wMainMenu) // Check if the Asset is assigned in the blueprint.
//	{
//		// Create the widget and store it.
//		MyMainMenu = CreateWidget<UUserWidget>(this, wMainMenu);
//
//		// now you can use the widget directly since you have a referance for it.
//		// Extra check to  make sure the pointer holds the widget.
//		if (MyMainMenu)
//		{
//			//let add it to the view port
//			MyMainMenu->AddToViewport();
//		}
//
//		//Show the Cursor.
//		bShowMouseCursor = true;
//	}
//}
//
//#include "VictoryMultiThreadTest.h"
//// https://wiki.unrealengine.com/Multi-Threading:_Task_Graph_System
////~~~ In the Game Thread ~~~
//
////timer to check when threads are done
////Please note timers must be in the game thread / main / normal thread
//void AMyPlayerController::VictoryCheckAllThreadsDone()
//{
//	if (VictoryMultiThreadTest::TasksAreComplete())
//	{
//		//Clear Timer
//		//GetWorldTimerManager().ClearTimer(this,
//		//	&AMyPlayerController::VictoryCheckAllThreadsDone);
//		GetWorldTimerManager().ClearTimer(OneSecTimerHandle);
//
//		ClientMessage("Multi Thread Test Done!");
//
//		//VShow("Prime Numbers Found:");
//		for (int32 v = 0; v < VictoryMultiThreadTest::PrimeNumbers.Num(); v++)
//		{
//			//VShow(FString::FromInt(v) + FString("~ "), VictoryMultiThreadTest::PrimeNumbers[v]);
//		}
//	}
//}
//
////Starting the Tasks / Threads
//void AMyPlayerController::StartThreadTest()
//{
//	VictoryMultiThreadTest::ThePC = this;
//	VictoryMultiThreadTest::FindPrimes(50000); //first 50,000 prime numbers
//	//Start a timer to check when all the threads are done!
//	//GetWorldTimerManager().SetTimer(this,
//	//	&AMyPlayerController::VictoryCheckAllThreadsDone, 1, true);
//	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AMyPlayerController::VictoryCheckAllThreadsDone);
//	EngineApi::GetWorldTimerManager().SetTimer(OneSecTimerHandle, TimerDelegate, 1, true);
//}