#include "MyProject.h"
#include "MyLevelScriptActorBase.h"

AMyLevelScriptActorBase::AMyLevelScriptActorBase(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	SolusLevelName = NAME_None;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//				Solus Level Begin Play
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Actor.h 		ReceiveBeginPlay()
void AMyLevelScriptActorBase::ReceiveBeginPlay()
{
	Super::ReceiveBeginPlay();
	//~~~~~~~~~~

	//UE_LOG(YourLog,Error,TEXT("STREAMING LEVEL BEGIN PLAY %s"), *GetName());
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		 			Solus Level End Play
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void AMyLevelScriptActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	/*
	UE_LOG(YourLog,Error,TEXT("STREAMING LEVEL UNSTREAMED (name should not be none) %s"), *GetName());
	UE_LOG(YourLog,Error,TEXT("Victory!!!"));
	UE_LOG(YourLog,Error,TEXT("RUN ALL UNSTREAMING LEVEL LOGIC HERE"));
	*/

	//Save Level Just Before Exiting
	SolusLevel__UpdateLevelSaveData();

	Super::OnRemoveFromWorld();
}

void AMyLevelScriptActorBase::SolusLevel__UpdateLevelSaveData()
{
	//Save Level Data
}

void AMyLevelScriptActorBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//~~~~~~~~~~~~~~

	//UE_LOG(YourLog,Warning,TEXT("Level Name Is: %s"), *SolusLevelName);
}