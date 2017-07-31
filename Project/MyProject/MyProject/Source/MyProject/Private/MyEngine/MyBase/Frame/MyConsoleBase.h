#pragma once

#include "Engine/Console.h"		// UConsole
#include "MyConsoleBase.generated.h"

/**
 * @brief
 在这里设置
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 ConsoleClassName=/Script/MyProject.MyTPConsole
 */

UCLASS()
class UMyConsoleBase : public UConsole
{
	GENERATED_UCLASS_BODY()
};