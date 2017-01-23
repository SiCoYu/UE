#include "MyProject.h"
#include "MyLevelScriptActor.h"

AMyLevelScriptActor::AMyLevelScriptActor(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	SolusLevelName = NAME_None;
}

bool AMyLevelScriptActor::RemoteEvent(FName EventName)
{
	return Super::RemoteEvent(EventName);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//				Solus Level Begin Play
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Actor.h 		ReceiveBeginPlay()
void AMyLevelScriptActor::ReceiveBeginPlay()
{
	Super::ReceiveBeginPlay();
	//~~~~~~~~~~

	//UE_LOG(YourLog,Error,TEXT("STREAMING LEVEL BEGIN PLAY %s"), *GetName());
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		 			Solus Level End Play
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void AMyLevelScriptActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	/*
	UE_LOG(YourLog,Error,TEXT("STREAMING LEVEL UNSTREAMED (name should not be none) %s"), *GetName());
	UE_LOG(YourLog,Error,TEXT("Victory!!!"));
	UE_LOG(YourLog,Error,TEXT("RUN ALL UNSTREAMING LEVEL LOGIC HERE"));
	*/

	//Save Level Just Before Exiting
	SolusLevel__UpdateLevelSaveData();

	//Super::OnRemoveFromWorld();
}

void AMyLevelScriptActor::SolusLevel__UpdateLevelSaveData()
{
	//Save Level Data
}

void AMyLevelScriptActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//~~~~~~~~~~~~~~

	//UE_LOG(YourLog,Warning,TEXT("Level Name Is: %s"), *SolusLevelName);
}