#ifndef __EditorWinLog_H
#define __EditorWinLog_H

#include "Logging/LogMacros.h"
#include "UnrealString.h"		// FString
#include "Internationalization/Text.h"	// FText
#include "UObject/Object.h" // UObject : public UObjectBaseUtility

#include "MLogType.h"
#include "MLogMacro.h"
#include "LogCategoryDef.h"

// https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
//DECLARE_LOG_CATEGORY_EXTERN(ComLog, Log, All);
//DECLARE_LOG_CATEGORY_EXTERN(ComWarning, Warning, All);
//DECLARE_LOG_CATEGORY_EXTERN(ComError, Error, All);

/**
 * @brief Editor 窗口日志
 * @brief MLogMacro.h 中使用 GetNameSafe，因此才继承 UObject
 */
class EditorWinLog : public UObject
{
public:
	EditorWinLog();
	void log(FString str, MLogType::MLogType type);
	void warn(FString str, MLogType::MLogType type);
	void error(FString str, MLogType::MLogType type);
};

#endif