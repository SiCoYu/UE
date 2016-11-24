#pragma once

#include "Logging/LogMacros.h"
/**
* @brief https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
*/

//General Log
DECLARE_LOG_CATEGORY_EXTERN(YourLog, Log, All);

//Logging during game startup
DECLARE_LOG_CATEGORY_EXTERN(YourInit, Log, All);

//Logging for your AI system
DECLARE_LOG_CATEGORY_EXTERN(YourAI, Log, All);

//Logging for Critical Errors that must always be addressed
DECLARE_LOG_CATEGORY_EXTERN(YourCriticalErrors, Log, All);