#ifndef __ClientScreenLog_H
#define __ClientScreenLog_H

#include "Logging/LogMacros.h"
#include "UnrealString.h"		// FString
#include "Internationalization/Text.h"	// FText
#include "Math/Color.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "MLogType.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief Client Screen �ͻ�����Ļ��־
 * @ref https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
 */
class ClientScreenLog
{
public:
	ClientScreenLog();
	void log(FString str, MLogType type);
	void warn(FString str, MLogType type);
	void error(FString str, MLogType type);
};

MY_END_NAMESPACE

#endif