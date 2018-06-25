#pragma once

#include "MyGameUserSettingsBase.h"
#include "MyTomGameUserSettings.generated.h"

UCLASS()
class UMyTomGameUserSettings : public UMyGameUserSettingsBase
{
	GENERATED_UCLASS_BODY()


	// interface UGameUserSettings
	virtual void SetToDefaults() override;
};