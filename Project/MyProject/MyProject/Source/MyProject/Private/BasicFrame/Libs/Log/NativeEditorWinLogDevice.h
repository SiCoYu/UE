#ifndef __NativeEditorWinLogDevice_H
#define __NativeEditorWinLogDevice_H

#include "Logging/LogMacros.h"
#include "UnrealString.h"		// FString
#include "Internationalization/Text.h"	// FText
#include "UObject/Object.h" // UObject : public UObjectBaseUtility

#include "MLogType.h"
#include "MLogMacro.h"
#include "LogCategoryDef.h"

#include "PlatformDefine.h"

MY_USING_NAMESPACE(MyNS)

// https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
//DECLARE_LOG_CATEGORY_EXTERN(ComLog, Log, All);
//DECLARE_LOG_CATEGORY_EXTERN(ComWarning, Warning, All);
//DECLARE_LOG_CATEGORY_EXTERN(ComError, Error, All);

/**
 * @brief Editor 窗口日志
 * @brief MLogMacro.h 中使用 GetNameSafe，因此才继承 UObject
 */
class NativeEditorWinLogDevice : public UObject
{
public:
	NativeEditorWinLogDevice();
	void log(FString str, MLogType type);
	void warn(FString str, MLogType type);
	void error(FString str, MLogType type);
};

#endif