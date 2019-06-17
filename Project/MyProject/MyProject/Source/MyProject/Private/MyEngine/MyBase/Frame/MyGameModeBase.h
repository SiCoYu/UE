#pragma once

//#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

// AGameModeBase 这个模式不会调用 Actor 的 BeginPlayer，因为 WorldSetting 中的 BeginPlyer
UCLASS(minimalapi)
//class AMyGameModeBase : public AGameModeBase
class AMyGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	AMyGameModeBase();
	AMyGameModeBase(const FObjectInitializer& ObjectInitializer);

	// ue4-控制台执行方法: http://blog.csdn.net/yangxuan0261/article/details/53969564
public:
	UFUNCTION(Exec)
	virtual void execInConsole(FString _str, int32 _num);

	// https://blog.csdn.net/ywjun0919/article/details/89246174
	FString CreateStreamInstance(UWorld* World, const FString& LongPackageName, const FVector Location, const FRotator Rotation);
	void LoadMap(const FString& LevelName);
};