#pragma once

#include "MyProject.h"
#include "MyProjectGameInstance.generated.h"

class AppFrame;

/**
 * @brief 
 https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
 https://wiki.unrealengine.com/Game_Instance,_Custom_Game_Instance_For_Inter-Level_Persistent_Data_Storage#Overview
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 GameInstanceClass=/Script/Solus.SolusGameInstance
 */

UCLASS(config=Game)
class UMyProjectGameInstance : public UGameInstance
{
public:
	GENERATED_UCLASS_BODY()

protected:
	AppFrame* m_appFrame;

public:
	virtual void Init() override;
};


