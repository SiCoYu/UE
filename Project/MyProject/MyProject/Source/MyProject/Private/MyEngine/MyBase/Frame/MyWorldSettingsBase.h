#pragma once

#include "GameFramework/WorldSettings.h"	// UWorldSettings
#include "MyWorldSettingsBase.generated.h"

/**
 * @brief �� MyProject\Config\DefaultEngine.ini ���������� WorldSettingsClassName=/Script/MyProject.MyWorldSettings�� �����ڱ༭�����ã� Engine ����
 */

UCLASS()
class AMyWorldSettingsBase : public AWorldSettings
{
	GENERATED_UCLASS_BODY()
};