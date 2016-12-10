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

void AMyProjectPlayerController::ServerTaunt_Implementation()
{
	// Only allow Taunt its been awhile since we last tried to commit Taunt.
	// TIMEXXX macros from https://wiki.unrealengine.com/Time_Macros
	if (TIMESINCE(LastTauntTime) > 5.0)
	{
		LastTauntTime = TIMENOW;
		// Don't commit Taunt if a Taunt attempt is already pending.
		if (!ISTIMERACTIVE(TimerHandle_Taunt))
		{
			// Delay the Taunt attempt a random amount to prevent trolling.
			SETTIMERH(TimerHandle_Taunt, AYourPlayerController::TauntTimer, FMath::FRandRange(1.5f, 3.0f), false);
		}
	}
}

void AMyProjectPlayerController::ExampleUsageOne()
{
	//In player controller class

	//location the PC is focused on
	const FVector Start = GetFocalLocation();

	//256 units in facing direction of PC (256 units in front of the camera)
	const FVector End = Start + GetControlRotation().Vector() * 256;

	//The trace data is stored here
	FHitResult HitData(ForceInit);

	//If Trace Hits anything
	if (UMyStaticFunctionLibrary::Trace(GetWorld(), GetPawn(), Start, End, HitData))
	{
		//Print out the name of the traced actor
		if (HitData.GetActor())
		{
			ClientMessage(HitData.GetActor()->GetName());

			//Print out distance from start of trace to impact point
			ClientMessage("Trace Distance: " + FString::SanitizeFloat(HitData.Distance));
		}
	}
}

void AMyProjectPlayerController::ExampleUsageTwo()
{
	//In player controller class

	//location the PC is focused on
	const FVector Start = GetFocalLocation();

	//2000 units in facing direction of PC (in front of the camera)
	const FVector End = Start + GetControlRotation().Vector() * 2000;

	//The trace data is stored here
	FHitResult HitData(ForceInit);

	//If Trace Hits anything (ignore the controlled pawn)
	if (UMyStaticFunctionLibrary::Trace(GetWorld(), GetPawn(), Start, End, HitData) && HitData.GetActor())
	{
		ClientMessage(HitData.GetActor()->GetName());

		//Print out the distance from the trace start to the impact point!
		ClientMessage("Distance from Trace Start to Impact: " + FString::SanitizeFloat(HitData.Distance));
	}
}

void AMyProjectPlayerController::ExampleUsageThree()
{
	//The trace data is stored here
	FHitResult HitData(ForceInit);

	//Actors to Ignore
	//  Ignore all AFlowers
	TArray<AActor*> ActorsToIgnore;
	for (TObjectIterator<AFlower> It; It; ++It)
	{
		ActorsToIgnore.Add(*It);
	}

	//Ignore the player character too!
	ActorsToIgnore.Add(GetPawn());

	//If Trace Hits anything
	if (UMyStaticFunctionLibrary::Trace(GetWorld(), GetPawn(), Start, End, ActorsToIgnore))
	{
		//Print out the name of the traced actor
		if (HitData.GetActor())
		{
			ClientMessage(HitData.GetActor()->GetName());

			//Print out distance from start of trace to impact point
			ClientMessage("Trace Distance: " + FString::SanitizeFloat(HitData.Distance));
		}
	}
}

void AMyProjectPlayerController::ExampleUsageFour()
{
	//In player controller class

	ACharacter* CharacterToTrace = //set to some character

		if (!CharacterToTrace) return;
	if (!CharacterToTrace->IsValidLowLevel()) return;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	//location the PC is focused on
	const FVector Start = GetFocalLocation();

	//256 units in facing direction of PC (256 units in front of the camera)
	const FVector End = Start + GetControlRotation().Vector() * 256;

	//The trace data is stored here
	FHitResult HitData(ForceInit);

	//If Trace Hits any part of the Mesh of the Character To Trace
	if (UMyStaticFunctionLibrary::Trace(CharacterToTrace->GetMesh(), Start, End, HitData))
	{
		//Print out the location of the impact on the Character's Mesh
		ClientMessage(HitData.ImpactPoint.ToString());

		//Print out distance from start of trace to impact point
		ClientMessage("Trace Distance: " + FString::SanitizeFloat(HitData.Distance));
	}
}