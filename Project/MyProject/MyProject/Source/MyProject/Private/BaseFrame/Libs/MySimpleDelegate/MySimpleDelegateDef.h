#pragma once

#include "MySimpleDelegateBase.h"
#include "MySimpleDelegate.h"
#include "MySimpleDelegateInstanceBase.h"
#include "MySimpleMethodDelegateInstance.h"

namespace MyNS
{
#define MY_MINI_FUNC_DECLARE_DELEGATE( DelegateName, ... ) \
	typedef MySimpleDelegate<__VA_ARGS__> DelegateName;
#define MY_MINI_DECLARE_DELEGATE( DelegateName ) MY_MINI_FUNC_DECLARE_DELEGATE( DelegateName, void )
#define MY_MINI_DECLARE_DELEGATE_RetVal( ReturnValueType, DelegateName ) MY_MINI_FUNC_DECLARE_DELEGATE( DelegateName, ReturnValueType )

#define MY_MINI_DECLARE_DELEGATE_OneParam( DelegateName, Param1Type ) MY_MINI_FUNC_DECLARE_DELEGATE( DelegateName, void, Param1Type )
#define MY_MINI_DECLARE_DELEGATE_RetVal_OneParam( ReturnValueType, DelegateName, Param1Type ) MY_MINI_FUNC_DECLARE_DELEGATE( DelegateName, ReturnValueType, Param1Type )

#define MY_MINI_DECLARE_DELEGATE_TwoParams( DelegateName, Param1Type, Param2Type ) MY_MINI_FUNC_DECLARE_DELEGATE( DelegateName, void, Param1Type, Param2Type )
#define MY_MINI_DECLARE_DELEGATE_RetVal_TwoParams( ReturnValueType, DelegateName, Param1Type, Param2Type ) MY_MINI_FUNC_DECLARE_DELEGATE( DelegateName, ReturnValueType, Param1Type, Param2Type )

#define MY_MINI_DECLARE_DELEGATE_ThreeParams( DelegateName, Param1Type, Param2Type, Param3Type ) MY_MINI_FUNC_DECLARE_DELEGATE( DelegateName, void, Param1Type, Param2Type, Param3Type )
#define MY_MINI_DECLARE_DELEGATE_RetVal_ThreeParams( ReturnValueType, DelegateName, Param1Type, Param2Type, Param3Type ) MY_MINI_FUNC_DECLARE_DELEGATE( DelegateName, ReturnValueType, Param1Type, Param2Type, Param3Type )
}