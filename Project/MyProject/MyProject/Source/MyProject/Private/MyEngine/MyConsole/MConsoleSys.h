#pragma once

#include "MConsoleSys.generated.h"

/**
 * @brief On engine startup, the state of console variables can be loaded from the file Engine/Config/ConsoleVariables.ini.
 * @brief You also can put the settings Engine/Config/BasEngine.ini e.g. 
 * @ref https://docs.unrealengine.com/latest/INT/Programming/Development/Tools/ConsoleManager/index.html
 */
UCLASS()
class UMConsoleSys : public UObject
{
	GENERATED_UCLASS_BODY()

	static TAutoConsoleVariable<int32> CVarRefractionQuality;
public:
	void init();
	void dispose();
	void registerConsoleVariable();
	void unregisterConsoleVariable();
};