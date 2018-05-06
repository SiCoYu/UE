#ifndef __MLogMacro_H
#define __MLogMacro_H

#pragma once

#include "Logging/LogMacros.h"
#include "EngineGlobals.h"	// GEngine
#include "UtilEngineWrap.h"		// GetWorld
#include "Engine/EngineBaseTypes.h"	// NM_Client
#include "UnrealString.h"		// FString
#include "Math/Color.h"	// FColor::White
#include "UObject/UObjectBaseUtility.h"		// GetNameSafe

//-----------------------------------------------------
/**
 * @brief https://wiki.unrealengine.com/Logs,_Printing_the_Class_Name,_Function_Name,_Line_Number_of_your_Calling_Code!
 */

 //Current Class Name + Function Name where this is called!
#define MLogMacro_CUR_CLASS_FUNC (FString(__FUNCTION__))

 //Current Class where this is called!
#define MLogMacro_CUR_CLASS (FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) )

 //Current Function Name where this is called!
#define MLogMacro_CUR_FUNC (FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2 ))

 //Current Line Number in the code where this is called!
#define MLogMacro_CUR_LINE  (FString::FromInt(__LINE__))

 //Current Class and Line Number where this is called!
#define MLogMacro_CUR_CLASS_LINE (MLogMacro_CUR_CLASS + "(" + MLogMacro_CUR_LINE + ")")

 //Current Function Signature where this is called!
#define MLogMacro_CUR_FUNCSIG (FString(__FUNCSIG__))


 //Victory Screen Message
 // 	Gives you the Class name and exact line number where you print a message to yourself!
#define MLogMacro_VSCREENMSG(Param1) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(JOYSTR_CUR_CLASS_LINE + ": " + Param1)) )

#define MLogMacro_VSCREENMSG2(Param1,Param2) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(MLogMacro_CUR_CLASS_LINE + ": " + Param1 + " " + Param2)) )

#define MLogMacro_VSCREENMSGF(Param1,Param2) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(MLogMacro_CUR_CLASS_LINE + ": " + Param1 + " " + FString::SanitizeFloat(Param2))) )

 //UE LOG!
#define MLogMacro_V_LOG(LogCat, Param1) 		UE_LOG(LogCat,Warning,TEXT("%s: %s"), *MLogMacro_CUR_CLASS_LINE, *FString(Param1))

#define MLogMacro_V_LOG2(LogCat, Param1,Param2) 	UE_LOG(LogCat,Warning,TEXT("%s: %s %s"), *MLogMacro_CUR_CLASS_LINE, *FString(Param1),*FString(Param2))

#define MLogMacro_V_LOGF(LogCat, Param1,Param2) 	UE_LOG(LogCat,Warning,TEXT("%s: %s %f"), *MLogMacro_CUR_CLASS_LINE, *FString(Param1),Param2)

#define MLogMacro_V_LOGM(LogCat, FormatString , ...) UE_LOG(LogCat,Warning,TEXT("%s: %s"), 	*MLogMacro_CUR_CLASS_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )

//------------------------------------------------------

/**
 * @brief https://wiki.unrealengine.com/Logs,_Printing_the_Class_Name,_Function_Name,_Line_Number_of_your_Calling_Code!
 */

#define MLogMacro_NETMODE_WORLD (((GEngine == nullptr) || (UtilEngineWrap::GetWorld() == nullptr)) ? TEXT("") \
        : (GEngine->GetNetMode(UtilEngineWrap::GetWorld()) == NM_Client) ? TEXT("[Client] ") \
        : (GEngine->GetNetMode(UtilEngineWrap::GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
        : (GEngine->GetNetMode(UtilEngineWrap::GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
        : TEXT("[Standalone] "))

#if _MSC_VER
#define MLogMacro_FUNC_NAME    TEXT(__FUNCTION__)
#else // FIXME - GCC?
#define MLogMacro_FUNC_NAME    TEXT(__func__)
#endif

#define MLogMacro_TRACE(Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_CYAN);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    if (Msg == "") \
    { \
        UE_LOG(MLogMacro_LogCategory, Log, TEXT("%s%s() : %s"), MLogMacro_NETMODE_WORLD, MLogMacro_FUNC_NAME, *GetNameSafe(this));\
    } \
    else \
    { \
        UE_LOG(MLogMacro_LogCategory, Log, TEXT("%s%s() : %s"), MLogMacro_NETMODE_WORLD, MLogMacro_FUNC_NAME, *Msg);\
    } \
    CLEAR_WARN_COLOR();\
}

#define TRACESTATIC(Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_CYAN);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(MLogMacro_LogCategory, Log, TEXT("%s() : %s"), MLogMacro_FUNC_NAME, *Msg);\
    CLEAR_WARN_COLOR();\
}

#define TRACEWARN(Format, ...) \
{ \
    SET_WARN_COLOR( COLOR_YELLOW );\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(MLogMacro_LogCategory, Log, TEXT("**WARNING** %s%s() : %s"), MLogMacro_NETMODE_WORLD, MLogMacro_FUNC_NAME, *Msg);\
    CLEAR_WARN_COLOR();\
}

#define TRACEERROR(Format, ...) \
{ \
    SET_WARN_COLOR( COLOR_RED );\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    UE_LOG(MLogMacro_LogCategory, Log, TEXT("**ERROR** %s%s() : %s"), MLogMacro_NETMODE_WORLD, MLogMacro_FUNC_NAME, *Msg);\
    CLEAR_WARN_COLOR();\
}

#define SCREENDEBUG(Format, ...) \
{ \
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    if (Msg == "") \
    { \
        TCHAR StdMsg[MAX_SPRINTF] = TEXT(""); \
        FCString::Sprintf(StdMsg, TEXT("%s%s() : %s"), MLogMacro_NETMODE_WORLD, MLogMacro_FUNC_NAME, *GetNameSafe(this)); \
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, StdMsg); \
    } \
    else \
    { \
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, Msg); \
    } \
}

DECLARE_LOG_CATEGORY_EXTERN(MLogMacro_LogCategory, Log, All);

//------------------------------------------------------

#endif