#pragma once

#include "Logging/LogMacros.h"

/**
 * @brief https://wiki.unrealengine.com/EnumToString_Macro
 */

// 关键就是这个宏
#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

UENUM()
enum class EUsesEnum : uint8
{
	UseEnum_Bad,
	UseEnum_Good,
	UseEnum_Nice,
	UseEnum_Naughty
};

class AYourClass
{
	void SomeFunction();
};

DECLARE_LOG_CATEGORY_EXTERN(LogSomething, Log, All);