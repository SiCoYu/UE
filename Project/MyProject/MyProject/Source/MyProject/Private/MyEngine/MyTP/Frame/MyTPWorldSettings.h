#pragma once

#include "MyWorldSettingsBase.h"	// UWorldSettings
#include "MyTPWorldSettings.generated.h"

/**
 * @brief MyWorldSettingsBase
 * MyProject\Config\DefaultEngine.ini
 * WorldSettingsClassName=/Script/MyProject.MyFlyWorldSettings
 * ��������ť [Project and Editor Settings] -- [World Settings]
 */

UCLASS()
class AMyTPWorldSettings : public AMyWorldSettingsBase
{
	GENERATED_UCLASS_BODY()
};