#pragma once

#include "GameFramework/GameUserSettings.h"
#include "MyGameUserSettingsBase.generated.h"

UCLASS()
class UMyGameUserSettingsBase : public UGameUserSettings
{
	GENERATED_UCLASS_BODY()


	// interface UGameUserSettings
	virtual void SetToDefaults() override;
};
