#pragma once

#include "MyWorldSettingsBase.h"	// UWorldSettings
#include "MyFlyWorldSettings.generated.h"

/**
 * @brief MyWorldSettingsBase
 MyProject\Config\DefaultEngine.ini
 WorldSettingsClassName=/Script/MyProject.MyFlyWorldSettings
 */

UCLASS()
class AMyFlyWorldSettings : public AMyWorldSettingsBase
{
	GENERATED_UCLASS_BODY()
};