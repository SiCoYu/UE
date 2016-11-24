#pragma once

#include "MyProjectUserSettings.generated.h"

UCLASS()
class UMyProjectUserSettings : public UGameUserSettings
{
	GENERATED_UCLASS_BODY()


	// interface UGameUserSettings
	virtual void SetToDefaults() override;
};
