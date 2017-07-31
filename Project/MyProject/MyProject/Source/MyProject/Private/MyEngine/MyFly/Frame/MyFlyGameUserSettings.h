#pragma once

#include "MyGameUserSettingsBase.h"
#include "MyFlyGameUserSettings.generated.h"

UCLASS()
class UMyFlyGameUserSettings : public UMyGameUserSettingsBase
{
	GENERATED_UCLASS_BODY()


	// interface UGameUserSettings
	virtual void SetToDefaults() override;
};