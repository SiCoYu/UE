#pragma once

#include "GameFramework/OnlineSession.h"	// UOnlineSession
#include "MyGameInstanceBase.h"
#include "MyTomGameInstance.generated.h"

/**
 * @brief 
 https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
 https://wiki.unrealengine.com/Game_Instance,_Custom_Game_Instance_For_Inter-Level_Persistent_Data_Storage#Overview
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 GameInstanceClass=/Script/MyProject.MyFlyGameInstance
 */

UCLASS(config=Game)
class UMyTomGameInstance : public UMyGameInstanceBase
{
public:
	GENERATED_UCLASS_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void FinishDestroy() override;

	virtual TSubclassOf<UOnlineSession> GetOnlineSessionClass() override;
};


