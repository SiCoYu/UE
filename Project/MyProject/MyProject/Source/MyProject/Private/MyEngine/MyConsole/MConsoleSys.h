#pragma once

/**
 * @brief On engine startup, the state of console variables can be loaded from the file Engine/Config/ConsoleVariables.ini.
 * @brief You also can put the settings Engine/Config/BasEngine.ini e.g. 
 * @ref https://docs.unrealengine.com/latest/INT/Programming/Development/Tools/ConsoleManager/index.html
 */
class MConsoleSys
{
	static TAutoConsoleVariable<int32> CVarRefractionQuality;
public:
	void init();
	void dispose();
	void registerConsoleVariable();
	void unregisterConsoleVariable();
};