#pragma once

#include "MyGameUserSettingsBase.h"
#include "MyTPGameUserSettings.generated.h"

UCLASS()
class UMyTPGameUserSettings : public UMyGameUserSettingsBase
{
	GENERATED_UCLASS_BODY()


	// interface UGameUserSettings
	virtual void SetToDefaults() override;
};