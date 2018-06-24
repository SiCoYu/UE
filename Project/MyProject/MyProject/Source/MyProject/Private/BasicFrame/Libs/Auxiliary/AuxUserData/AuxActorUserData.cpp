#include "MyProject.h"
#include "AuxActorUserData.h"

UAuxActorUserData::UAuxActorUserData(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAuxActorUserData::BeginPlay()
{
	Super::BeginPlay();
}

void UAuxActorUserData::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UAuxActorUserData::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}