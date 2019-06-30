#pragma once

#include "MyGameUserSettingsBase.h"
#include "MyOaGameUserSettings.generated.h"

UCLASS()
class UMyOaGameUserSettings : public UMyGameUserSettingsBase
{
	GENERATED_UCLASS_BODY()

	// interface UGameUserSettings
	virtual void SetToDefaults() override;
};