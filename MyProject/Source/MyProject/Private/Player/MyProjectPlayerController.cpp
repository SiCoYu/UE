#include "MyProject.h"
#include "MyProjectPlayerController.h"

AMyProjectPlayerController::AMyProjectPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* Initialize The Values */
	PawnToUseA = NULL;
	PawnToUseB = NULL;

	/* Make sure the PawnClass is Replicated */
	bReplicates = true;
}

void AMyProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	DeterminePawnClass();
}

// Pawn Class
void AMyProjectPlayerController::DeterminePawnClass_Implementation()
{
	if (IsLocalController()) //Only Do This Locally (NOT Client-Only, since Server wants this too!)
	{
		/* Load Text File Into String Array */
		TArray<FString> TextStrings;
		const FString FilePath = FPaths::GameDir() + "Textfiles/PlayerSettings.txt";

		/* Use PawnA if the Text File tells us to */
		if (TextStrings[0] == "PawnA")
		{
			ServerSetPawn(PawnToUseA);
			return;
		}

		/* Otherwise, Use PawnB :) */
		ServerSetPawn(PawnToUseB);
		return;
	}
}

bool AMyProjectPlayerController::ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass)
{
	return true;
}

void AMyProjectPlayerController::ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass)
{
	MyPawnClass = InPawnClass;

	/* Just in case we didn't get the PawnClass on the Server in time... */
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}

// Replication
void AMyProjectPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AMyPlayerController, MyPawnClass);
}

bool AMyProjectPlayerController::IsActorWithinTheBoundsOfStreamedInLeve()
{
	bool ret = false;
	//Get the Currently Streamed Levels
	const TArray<ULevelStreaming*>& StreamedLevels = GetWorld()->StreamingLevels;

	for (const ULevelStreaming* EachLevelStreaming : StreamedLevels)
	{
		if (!EachLevelStreaming)
		{
			continue;
		}

		ULevel* EachLevel = EachLevelStreaming->GetLoadedLevel();

		//Is This Level Valid and Visible?
		if (!EachLevel || !EachLevel->bIsVisible)
		{
			continue;
		}

		//Print Name of current Level Streaming to know which level the unit is in!
		ClientMessage(EachLevelStreaming->GetWorldAssetPackageName());

		//Is the Player Location Within this Level's Bounds
		if (ALevelBounds::CalculateLevelBounds(EachLevel).IsInside(GetPawn()->GetActorLocation()))
		{
			ClientMessage("Yes Player Is Within This Level");
			ret = true;
		}

		return ret;
	}
}