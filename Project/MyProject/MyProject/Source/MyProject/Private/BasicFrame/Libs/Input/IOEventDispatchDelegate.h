#pragma once

#include "TypeDef.h"
#include "PlatformDefine.h"
#include "MySimpleDelegateDef.h"

struct FKey;
class FName;

/**
* @brief IOEventDispatchDelegate.h
*/
MY_BEGIN_NAMESPACE(MyNS)

/**
 * @file IOEventDispatchDelegate.h
 */

MY_MINI_DECLARE_DELEGATE_RetVal_OneParam(bool, KeyEventDispatchDelegate, FKey);
MY_MINI_DECLARE_DELEGATE_RetVal_OneParam(float, AxisEventDispatchDelegate, FName);
MY_MINI_DECLARE_DELEGATE(ScreenResizeEventDispatchDelegate);

MY_END_NAMESPACE