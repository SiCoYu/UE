#pragma once

#include "MyGameUserSettingsBase.h"
#include "MyGameUserSettings.generated.h"

UCLASS()
class UMyGameUserSettings : public UMyGameUserSettingsBase
{
	GENERATED_UCLASS_BODY()


	// interface UGameUserSettings
	virtual void SetToDefaults() override;
};