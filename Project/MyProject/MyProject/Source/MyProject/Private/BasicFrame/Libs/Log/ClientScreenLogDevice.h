#ifndef __ClientScreenLogDevice_H
#define __ClientScreenLogDevice_H

#include "Logging/LogMacros.h"
#include "UnrealString.h"		// FString
#include "Internationalization/Text.h"	// FText
#include "Math/Color.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "MLogType.h"
#include "LogDeviceBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief Client Screen 客户端屏幕日志
 * @ref https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
 */
class ClientScreenLogDevice : public LogDeviceBase
{
public:
	ClientScreenLogDevice();
	void log(FString str, MLogType type);
	void warn(FString str, MLogType type);
	void error(FString str, MLogType type);
};

MY_END_NAMESPACE

#endif