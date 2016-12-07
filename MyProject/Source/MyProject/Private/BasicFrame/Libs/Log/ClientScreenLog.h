#ifndef __ClientScreenLog_H
#define __ClientScreenLog_H

#include "Logging/LogMacros.h"
#include "UnrealString.h"		// FString
#include "Internationalization/Text.h"	// FText
#include "Math/Color.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

#include "MLogType.h"

// https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime

/**
 * @brief Client Screen 客户端屏幕日志
 */
class ClientScreenLog
{
public:
	ClientScreenLog();
	void log(FString str, MLogType::MLogType type);
	void warn(FString str, MLogType::MLogType type);
	void error(FString str, MLogType::MLogType type);
};

#endif