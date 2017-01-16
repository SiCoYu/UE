#pragma once

#include "MyProject.h"
#include "MyGameInstanceBase.h"
#include "MyTPGameInstance.generated.h"

/**
 * @brief 
 https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
 https://wiki.unrealengine.com/Game_Instance,_Custom_Game_Instance_For_Inter-Level_Persistent_Data_Storage#Overview
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 GameInstanceClass=/Script/Solus.SolusGameInstance
 */

UCLASS(config=Game)
class UMyTPGameInstance : public UMyGameInstanceBase
{
public:
	GENERATED_UCLASS_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void FinishDestroy() override;

	virtual TSubclassOf<UOnlineSession> GetOnlineSessionClass() override;
};


