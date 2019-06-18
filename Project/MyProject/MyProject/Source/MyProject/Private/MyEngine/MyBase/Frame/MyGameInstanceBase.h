#pragma once

#include "Engine/GameInstance.h"
#include "PlatformDefine.h"
#include "MyGameInstanceBase.generated.h"

MY_BEGIN_NAMESPACE(MyNS)

class AppFrame;

MY_END_NAMESPACE

MY_USING_NAMESPACE(MyNS)

class UPackage;

/**
 * @brief 
 https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
 https://wiki.unrealengine.com/Game_Instance,_Custom_Game_Instance_For_Inter-Level_Persistent_Data_Storage#Overview
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 GameInstanceClass=/Script/MyProject.MyTPGameInstance
 */

UCLASS(config=Game)
class UMyGameInstanceBase : public UGameInstance
{
public:
	GENERATED_UCLASS_BODY()

protected:
	AppFrame* mAppFrame;
	FName mCachedLevelName;
	UPackage* mLevelPackage;

public:
	//virtual void Tick(float DeltaSeconds) override;

	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void FinishDestroy() override;

	virtual TSubclassOf<UOnlineSession> GetOnlineSessionClass() override;

	// ue4-控制台执行方法: http://blog.csdn.net/yangxuan0261/article/details/53969564
	virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;

	// https://answers.unrealengine.com/questions/599789/view.html
	void LoadMapAsync(FName LevelName);
	void FinishedStreamingLevel(const FName& PackageName, UPackage* InLevelPackage, EAsyncLoadingResult::Type Result);
};