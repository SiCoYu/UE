#ifndef __ClientWinLog_H
#define __ClientWinLog_H

#include "Logging/LogMacros.h"
#include "UnrealString.h"		// FString
#include "Internationalization/Text.h"	// FText
#include "GameFramework/PlayerController.h"

#include "MLogType.h"

// https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime

/**
 * @brief Client ¥∞ø⁄»’÷æ, Pressing the ~ key in Unreal brings up the client console. 
 */
class ClientWinLog
{
protected:
	APlayerController* mPlayerController;

public:
	ClientWinLog();
	void log(FString str, MLogType::MLogType type);
	void warn(FString str, MLogType::MLogType type);
	void error(FString str, MLogType::MLogType type);
};

#endif