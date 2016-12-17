#include "MyProject.h"
#include "MyCharacter.h"
#include "GameFramework/HUD.h"
#include "UI/MyHUD.h"
#include "Common.h"
#include "UIFormID.h"
#include "UIPack.h"
#include "MyPlayerController.h"
#include "UITestCanvas.h"
#include "GameFramework/PlayerStart.h"
#include "MyPlayerStart.h"
#include "MyCharacter.h"
#include "MyPlayerState.h"
#include "MyGameMode.h"

AMyGameMode::AMyGameMode(const FObjectInitializer& ObjectInitializer)
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

	// https://wiki.unrealengine.com/Spawn_Different_Pawns_For_Players_in_Multiplayer
	PlayerControllerClass = AMyPlayerController::StaticClass();

	// https://wiki.unrealengine.com/Slate,_Simple_C%2B%2B_Chat_System
	PlayerStateClass = AMyPlayerState::StaticClass();

	/* use this is you wish to extend the c++ into a bp and assign the bp to the class
	static ConstructorHelpers::FClassFinder<AMyHUD> hudclassobj(TEXT("Blueprint'/MyHUD.MyHUD_C'"));
	if (hudclassobj.Class != NULL)
	HUDClass = hudclassobj.Class;

	static ConstructorHelpers::FClassFinder<AMyPlayerState> psclassobj(TEXT("Blueprint'/MyPlayerState.MyPlayerState_C'"));
	if (psclassobj.Class != NULL)
	PlayerStateClass = psclassobj.Class;
	*/
}

UClass* AMyGameMode::GetDefaultPawnClassForController(AController* InController)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(InController);

	UClass* PawnClass = PawnTypes.Find(PlayerController->CurrentPawnData.Type);

	return PawnClass;
}

void AMyGameMode::StartPlay()
{
	Super::StartPlay();
	// 各种初始化
	EngineApi::showCursor();

	// 各种 UI 测试
	TestUI();
}

void AMyGameMode::TestUI()
{
	// Test 加载 UIPack
	//GUiMgr->loadForm<UUIPack>(eUIPack);
	GUiMgr->loadForm<UUITestCanvas>(eUITestCanvas);
}

// https://wiki.unrealengine.com/Survival_Sample_Game:_Section_4
void AMyGameMode::RestartPlayer(class AController* NewPlayer)
{
	// ...

	/* Look for a live player to spawn next to */
	FVector SpawnOrigin = FVector::ZeroVector;
	FRotator StartRotation = FRotator::ZeroRotator;
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		AMyCharacter* MyCharacter = Cast<AMyCharacter>(*It);
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
	FVector StartLocation = UNavigationSystem::GetRandomReachablePointInRadius(NewPlayer, SpawnOrigin, 250.0f);

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

AActor* AMyGameMode::ChoosePlayerStart(AController* Player)
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
bool AMyGameMode::IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Controller)
{
	if (Controller == nullptr || Controller->PlayerState == nullptr)
		return true;

	/* Check for extended playerstart class */
	AMyPlayerStart* MyPlayerStart = Cast<AMyPlayerStart>(SpawnPoint);
	if (MyPlayerStart)
	{
		return MyPlayerStart->GetIsPlayerOnly() && !Controller->PlayerState->bIsABot;
	}

	/* Cast failed, Anyone can spawn at the base playerstart class */
	return true;
}

bool AMyGameMode::IsSpawnpointPreferred(APlayerStart* SpawnPoint, AController* Controller)
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
		AMyPlayerStart* MyPlayerStart = Cast<AMyPlayerStart>(SpawnPoint);
		if (MyPlayerStart)
		{
			return MyPlayerStart->GetIsPlayerOnly() && !Controller->PlayerState->bIsABot;
		}
	}

	return false;
}