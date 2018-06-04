#pragma once

/**
 * @brief Core 所有头文件，只能在 cpp 文件中包含这个文件，不允许在其它功能性头文件中包含这个头文件
 */
#include "GObject.h"
#include "SafePointer.h"

#include "MySharedPointer.h"
#include "MyMemoryAlloc.h"
#include "TypeDef.h"

#include "MClassMacros.h"
#include "MClassInfo.h"
#include "MClassFactory.h"