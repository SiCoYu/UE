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

FString AMyGameModeBase::CreateStreamInstance(UWorld* World, const FString& LongPackageName, const FVector Location, const FRotator Rotation)
{
	const FString ShortPackageName = FPackageName::GetShortName(LongPackageName);
	const FString PackagePath = FPackageName::GetLongPackagePath(LongPackageName);
	FString UniqueLevelPackageName = PackagePath + TEXT("/") + World->StreamingLevelsPrefix + ShortPackageName;
	// Setup streaming level object that will load specified map
	ULevelStreamingDynamic* StreamingLevel = NewObject<ULevelStreamingDynamic>(World, ULevelStreamingDynamic::StaticClass(), NAME_None, RF_Transient, NULL);
	StreamingLevel->SetWorldAssetByPackageName(FName(*UniqueLevelPackageName));
	StreamingLevel->LevelColor = FColor::MakeRandomColor();

	StreamingLevel->LevelTransform = FTransform(Rotation, Location);
	// Map to Load
	StreamingLevel->PackageNameToLoad = FName(*LongPackageName);

	World->AddStreamingLevel(StreamingLevel);
	return UniqueLevelPackageName;
}

void AMyGameModeBase::LoadMap(const FString& LevelName)
{
	FString LongPackageName;
	bool bOutSuccess = FPackageName::SearchForPackageOnDisk(LevelName, &LongPackageName);
	if (!bOutSuccess)
	{
		return;
	}
	UWorld* world = GetWorld();
	FString name = CreateStreamInstance(world, LongPackageName, FVector::ZeroVector, FRotator::ZeroRotator);
	UGameplayStatics::LoadStreamLevel(world, FName(*LevelName), true, true, FLatentActionInfo());
}

//void AMyGameModeBase::StartPlay()
//{
//	LoadMap("StarterMap");
//}