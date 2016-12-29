#pragma once

#include "MyUserSettings.generated.h"

UCLASS()
class UMyUserSettings : public UGameUserSettings
{
	GENERATED_UCLASS_BODY()


	// interface UGameUserSettings
	virtual void SetToDefaults() override;
};
