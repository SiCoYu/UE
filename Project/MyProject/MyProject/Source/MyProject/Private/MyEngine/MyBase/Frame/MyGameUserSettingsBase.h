#pragma once

#include "GameFramework/GameUserSettings.h"
#include "MyGameUserSettingsBase.generated.h"

/**
 * @brief
 在这里设置
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 GameUserSettingsClassName=/Script/MyProject.MyTPUserSettings
 */

UCLASS()
class UMyGameUserSettingsBase : public UGameUserSettings
{
	GENERATED_UCLASS_BODY()


	// interface UGameUserSettings
	virtual void SetToDefaults() override;
};
