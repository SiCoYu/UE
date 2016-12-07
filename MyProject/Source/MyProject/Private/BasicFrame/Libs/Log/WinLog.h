#ifndef __WinLog_H
#define __WinLog_H

#include "Logging/LogMacros.h"
#include "UnrealString.h"		// FString
#include "Internationalization/Text.h"	// FText

#include "MLogType.h"

// https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
DECLARE_LOG_CATEGORY_EXTERN(ComLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ComWarning, Warning, All);
DECLARE_LOG_CATEGORY_EXTERN(ComError, Error, All);

class WinLog
{
public:
	WinLog();
	void log(FString str, MLogType::MLogType type);
	void warn(FString str, MLogType::MLogType type);
	void error(FString str, MLogType::MLogType type);
};

#endif