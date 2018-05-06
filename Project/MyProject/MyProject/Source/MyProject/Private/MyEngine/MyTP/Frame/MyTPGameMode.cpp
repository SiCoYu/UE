#include "MyProject.h"
#include "MyTPGameMode.h"
#include "MyTpCharacter.h"
#include "GameFramework/HUD.h"
#include "MyHUD.h"
#include "Common.h"
#include "UiFormId.h"
#include "UiPack.h"
#include "MyTPPlayerController.h"
#include "UiTestCanvas.h"
#include "GameFramework/PlayerStart.h"
#include "MyTPPlayerStart.h"
#include "MyTPCharacter.h"
#include "MyPlayerState.h"
#include "MyGameState.h"
#include "MyTPGameSession.h"
#include "MySpectatorPawn.h"

AMyTPGameMode::AMyTPGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	// 最新的 ThirdPerson 资源存放文件夹又改了
	// ThirdPerson Cpp 资源加载
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));

	// 通过 BP 资源设置
	// ThirdPerson Blueprint 资源加载
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/MyAsset/MyTP/ThirdPersonCPP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		this->DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//static ConstructorHelpers::FClassFinder<AHUD> HUBBPClass(TEXT("/Game/Blueprints/HUB"));
	//if (HUBBPClass.Class != NULL)
	//{
		//HUDClass = HUBBPClass.Class;
	this->HUDClass = AMyHUD::StaticClass();
	//}

	// https://wiki.unrealengine.com/Spawn_Different_Pawns_For_Players_in_Multiplayer
	this->PlayerControllerClass = AMyTPPlayerController::StaticClass();

	this->GameStateClass = AMyGameState::StaticClass();

	// https://wiki.unrealengine.com/Slate,_Simple_C%2B%2B_Chat_System
	this->PlayerStateClass = AMyPlayerState::StaticClass();

	/* use this is you wish to extend the c++ into a bp and assign the bp to the class
	static ConstructorHelpers::FClassFinder<AMyHUD> hudclassobj(TEXT("Blueprint'/MyHUD.MyHUD_C'"));
	if (hudclassobj.Class != NULL)
	HUDClass = hudclassobj.Class;

	static ConstructorHelpers::FClassFinder<AMyPlayerState> psclassobj(TEXT("Blueprint'/MyPlayerState.MyPlayerState_C'"));
	if (psclassobj.Class != NULL)
	PlayerStateClass = psclassobj.Class;
	*/

	this->GameSessionClass = AMyTPGameSession::StaticClass();
	this->SpectatorClass = AMySpectatorPawn::StaticClass();
}

UClass* AMyTPGameMode::GetDefaultPawnClassForController(AController* InController)
{
	AMyTPPlayerController* PlayerController = Cast<AMyTPPlayerController>(InController);

	UClass* PawnClass = PawnTypes.Find(PlayerController->CurrentPawnData.Type);

	return PawnClass;
}

void AMyTPGameMode::StartPlay()
{
	Super::StartPlay();
	// 各种初始化
	//EngineApi::showCursor();

	// 各种 UI 测试
	//TestUI();
}

void AMyTPGameMode::TestUI()
{
	// Test 加载 UIPack
	//GUiMgr->loadForm<UUiPack>(eUiPack);
	GUiMgr->loadForm<UUiTestCanvas>(eUiTestCanvas);
}

// https://wiki.unrealengine.com/Survival_Sample_Game:_Section_4
void AMyTPGameMode::RestartPlayer(class AController* NewPlayer)
{
	/* Look for a live player to spawn next to */
	FVector SpawnOrigin = FVector::ZeroVector;
	FRotator StartRotation = FRotator::ZeroRotator;
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		AMyTPCharacter* MyCharacter = Cast<AMyTPCharacter>(*It);
		if (MyCharacter && MyCharacter->IsAlive())
		{
			/* Get the origin of the first player we can find */
			SpawnOrigin = MyCharacter->GetActorLocation();
			StartRotation = MyCharacter->GetActorRotation();
			break;
		}
	}

	/* No player is alive (yet) - spawn using one of the PlayerStarts */
	if (SpawnOrigin == FVector::ZeroVector)
	{
		Super::RestartPlayer(NewPlayer);
		return;
	}

	// Engine\Source\Runtime\Engine\Classes\AI\Navigation\NavigationData.h
	// DEPRECATED(4.8, "GetRandomPointInRadius is deprecated, please use GetRandomReachablePointInRadius")
	/* Get a point on the nav mesh near the other player */
	//FVector StartLocation = UNavigationSystem::GetRandomPointInRadius(NewPlayer, SpawnOrigin, 250.0f);
	// UE4 4.17: warning C4996: 'UNavigationSystem::GetRandomReachablePointInRadius': This version of GetRandomReachablePointInRadius is deprecated. Please use the new version Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//FVector StartLocation = UNavigationSystem::GetRandomReachablePointInRadius(NewPlayer, SpawnOrigin, 250.0f);
	// ref: UnrealEngine\Engine\Source\Runtime\Engine\Private\AI\Navigation\NavigationSystem.cpp
	// FVector UNavigationSystem::GetRandomReachablePointInRadius(UObject* WorldContextObject, const FVector& Origin, float Radius, ANavigationData* NavData, TSubclassOf<UNavigationQueryFilter> FilterClass)
	UWorld* World = GEngine->GetWorldFromContextObject(NewPlayer, EGetWorldErrorMode::LogAndReturnNull);
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(World);
	FNavLocation StartLocation;
	bool ret = NavSys->GetRandomReachablePointInRadius(SpawnOrigin, 250.0f, StartLocation);

	// Try to create a pawn to use of the default class for this player
	if (NewPlayer->GetPawn() == nullptr && GetDefaultPawnClassForController(NewPlayer) != nullptr)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Instigator = Instigator;
		APawn* ResultPawn = GetWorld()->SpawnActor<APawn>(GetDefaultPawnClassForController(NewPlayer), StartLocation, StartRotation, SpawnInfo);
		if (ResultPawn == nullptr)
		{
			UE_LOG(LogGameMode, Warning, TEXT("Couldn't spawn Pawn of type %s at %s"), *GetNameSafe(DefaultPawnClass), &StartLocation);
		}
		NewPlayer->SetPawn(ResultPawn);
	}

	if (NewPlayer->GetPawn() == nullptr)
	{
		NewPlayer->FailedToSpawnPawn();
	}
	else
	{
		NewPlayer->Possess(NewPlayer->GetPawn());

		// If the Pawn is destroyed as part of possession we have to abort
		if (NewPlayer->GetPawn() == nullptr)
		{
			NewPlayer->FailedToSpawnPawn();
		}
		else
		{
			// Set initial control rotation to player start's rotation
			NewPlayer->ClientSetRotation(NewPlayer->GetPawn()->GetActorRotation(), true);

			FRotator NewControllerRot = StartRotation;
			NewControllerRot.Roll = 0.f;
			NewPlayer->SetControlRotation(NewControllerRot);

			SetPlayerDefaults(NewPlayer->GetPawn());
		}
	}
}

AActor* AMyTPGameMode::ChoosePlayerStart(AController* Player)
{
	TArray<APlayerStart*> PreferredSpawns;
	TArray<APlayerStart*> FallbackSpawns;

	for (int32 i = 0; i < PlayerStarts.Num(); i++)
	{
		APlayerStart* TestStart = PlayerStarts[i];
		if (IsSpawnpointAllowed(TestStart, Player))
		{
			if (IsSpawnpointPreferred(TestStart, Player))
			{
				PreferredSpawns.Add(TestStart);
			}
			else
			{
				FallbackSpawns.Add(TestStart);
			}
		}
	}

	APlayerStart* BestStart = nullptr;
	if (PreferredSpawns.Num() > 0)
	{
		BestStart = PreferredSpawns[FMath::RandHelper(PreferredSpawns.Num())];
	}
	else if (FallbackSpawns.Num() > 0)
	{
		BestStart = FallbackSpawns[FMath::RandHelper(FallbackSpawns.Num())];
	}

	return BestStart ? BestStart : Super::ChoosePlayerStart(Player);
}

/* Check to see if a player and/or AI may spawn at the PlayerStart */
bool AMyTPGameMode::IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Controller)
{
	if (Controller == nullptr || Controller->PlayerState == nullptr)
		return true;

	/* Check for extended playerstart class */
	AMyTPPlayerStart* MyPlayerStart = Cast<AMyTPPlayerStart>(SpawnPoint);
	if (MyPlayerStart)
	{
		return MyPlayerStart->GetIsPlayerOnly() && !Controller->PlayerState->bIsABot;
	}

	/* Cast failed, Anyone can spawn at the base playerstart class */
	return true;
}

bool AMyTPGameMode::IsSpawnpointPreferred(APlayerStart* SpawnPoint, AController* Controller)
{
	if (SpawnPoint)
	{
		/* Iterate all pawns to check for collision overlaps with the spawn point */
		const FVector SpawnLocation = SpawnPoint->GetActorLocation();
		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
		{
			ACharacter* OtherPawn = Cast<ACharacter>(*It);
			if (OtherPawn)
			{
				const float CombinedHeight = (SpawnPoint->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + OtherPawn->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) * 2.0f;
				const float CombinedWidth = SpawnPoint->GetCapsuleComponent()->GetScaledCapsuleRadius() + OtherPawn->GetCapsuleComponent()->GetScaledCapsuleRadius();
				const FVector OtherLocation = OtherPawn->GetActorLocation();

				// Check if player overlaps the playerstart
				if (FMath::Abs(SpawnLocation.Z - OtherLocation.Z) < CombinedHeight && (SpawnLocation - OtherLocation).Size2D() < CombinedWidth)
				{
					return false;
				}
			}
		}

		/* Check if spawnpoint is exclusive to players */
		AMyTPPlayerStart* MyPlayerStart = Cast<AMyTPPlayerStart>(SpawnPoint);
		if (MyPlayerStart)
		{
			return MyPlayerStart->GetIsPlayerOnly() && !Controller->PlayerState->bIsABot;
		}
	}

	return false;
}