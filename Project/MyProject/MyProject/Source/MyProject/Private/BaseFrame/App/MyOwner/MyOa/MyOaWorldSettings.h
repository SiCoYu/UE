#pragma once

#include "MyWorldSettingsBase.h"	// UWorldSettings
#include "MyOaWorldSettings.generated.h"

/**
 * @brief MyWorldSettingsBase
 * MyProject\Config\DefaultEngine.ini
 * WorldSettingsClassName=/Script/MyProject.MyFlyWorldSettings
 * ��������ť [Project and Editor Settings] -- [World Settings]
 */

UCLASS()
class AMyOaWorldSettings : public AMyWorldSettingsBase
{
	GENERATED_UCLASS_BODY()
};