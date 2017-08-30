#pragma once

#include "Logging/LogMacros.h"

/**
 * @brief https://wiki.unrealengine.com/EnumToString_Macro
 */

// UE4 4.17 : warning C4996: 'UEnum::GetEnumName': GetEnumName is deprecated, call GetNameStringByIndex instead Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
// 关键就是这个宏
//#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )
#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetNameStringByIndex((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

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