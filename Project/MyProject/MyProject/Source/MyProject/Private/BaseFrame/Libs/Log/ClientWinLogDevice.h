#ifndef __ClientWinLogDevice_H
#define __ClientWinLogDevice_H

#include "Logging/LogMacros.h"
#include "UnrealString.h"		// FString
#include "Internationalization/Text.h"	// FText
#include "GameFramework/PlayerController.h"
#include "MLogType.h"
#include "LogDeviceBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)


/**
 * @brief Client ¥∞ø⁄»’÷æ, Pressing the ~ key in Unreal brings up the client console. 
 * @ref https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
 */
class ClientWinLogDevice : public LogDeviceBase
{
protected:
	APlayerController* mPlayerController;

public:
	ClientWinLogDevice();
	void log(FString str, MLogType type);
	void warn(FString str, MLogType type);
	void error(FString str, MLogType type);
};

MY_END_NAMESPACE

#endif