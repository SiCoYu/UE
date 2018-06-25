#pragma once

#include "MyGameUserSettingsBase.h"
#include "MyTomUserSettings.generated.h"

/**
 * @brief
 在这里设置
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 GameUserSettingsClassName=/Script/MyProject.MyTPUserSettings
 */

UCLASS()
class UMyTomUserSettings : public UMyGameUserSettingsBase
{
	GENERATED_UCLASS_BODY()
};