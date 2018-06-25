#pragma once

#include "MyGameUserSettingsBase.h"
#include "MyTomUserSettings.generated.h"

/**
 * @brief
 ����������
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 GameUserSettingsClassName=/Script/MyProject.MyTPUserSettings
 */

UCLASS()
class UMyTomUserSettings : public UMyGameUserSettingsBase
{
	GENERATED_UCLASS_BODY()
};