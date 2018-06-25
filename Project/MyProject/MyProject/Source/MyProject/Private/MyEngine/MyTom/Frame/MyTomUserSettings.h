#pragma once

#include "MyGameUserSettingsBase.h"
#include "MyFlyUserSettings.generated.h"

/**
 * @brief
 在这里设置
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 GameUserSettingsClassName=/Script/MyProject.MyTPUserSettings
 */

UCLASS()
class UMyFlyUserSettings : public UMyGameUserSettingsBase
{
	GENERATED_UCLASS_BODY()
};