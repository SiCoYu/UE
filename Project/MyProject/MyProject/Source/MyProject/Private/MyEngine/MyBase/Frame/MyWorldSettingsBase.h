#pragma once

#include "GameFramework/WorldSettings.h"	// UWorldSettings
#include "MyWorldSettingsBase.generated.h"

/**
 * @brief 在 MyProject\Config\DefaultEngine.ini 这里面设置 WorldSettingsClassName=/Script/MyProject.MyWorldSettings。 或者在编辑器设置， Engine 区域
 */

UCLASS()
class AMyWorldSettingsBase : public AWorldSettings
{
	GENERATED_UCLASS_BODY()
};