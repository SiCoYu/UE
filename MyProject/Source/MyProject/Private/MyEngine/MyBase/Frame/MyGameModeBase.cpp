#include "MyProject.h"
#include "MyGameModeBase.h"
#include "MyFlyPawn.h"
#include "LogCategoryDef.h"

AMyGameModeBase::AMyGameModeBase()
{
	
}

AMyGameModeBase::AMyGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void AMyGameModeBase::execInConsole(FString _str, int32 _num)
{
	FString str = FString::Printf(TEXT("--- %s - %d"), *_str, _num);
	UE_LOG(ComLog, Warning, TEXT("--- %s - %d"), *_str, _num);
}