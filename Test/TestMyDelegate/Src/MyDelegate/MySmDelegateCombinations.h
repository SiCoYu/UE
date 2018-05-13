#pragma once

#include "MySmDelegateSignatureImpl.h"

using namespace MyNS;

#define FUNC_DECLARE_DELEGATE( DelegateName, ... ) \
	typedef MySmBaseDelegate<__VA_ARGS__> DelegateName;

#define DECLARE_DELEGATE_ThreeParams( DelegateName, Param1Type, Param2Type, Param3Type ) FUNC_DECLARE_DELEGATE( DelegateName, void, Param1Type, Param2Type, Param3Type )