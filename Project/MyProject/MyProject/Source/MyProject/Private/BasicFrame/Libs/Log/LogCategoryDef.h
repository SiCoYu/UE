#ifndef __LogCategoryDef_H
#define __LogCategoryDef_H

#include "Logging/LogMacros.h"

// https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
DECLARE_LOG_CATEGORY_EXTERN(ComLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ComWarning, Warning, All);
DECLARE_LOG_CATEGORY_EXTERN(ComError, Error, All);

#endif