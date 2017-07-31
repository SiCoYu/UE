#pragma once

#include "GameFramework/PlayerController.h"
#include "RWConfigFilePlayerController.generated.h"

/**
* @brief https://wiki.unrealengine.com/Config_Files,_Read_%26_Write_to_Config_Files
*/

UCLASS()
class ARWConfigFilePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void VictoryConfigGetTests();
	void VictoryConfigSetTests();
	void Flush();
};