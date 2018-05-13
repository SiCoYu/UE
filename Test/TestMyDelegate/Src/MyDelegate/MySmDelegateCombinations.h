#pragma once

#include "MySmBaseDelegate.h"

#define FUNC_DECLARE_DELEGATE( DelegateName, ... ) \
	typedef MyNS::MySmBaseDelegate<__VA_ARGS__> DelegateName;

#define DECLARE_DELEGATE_ThreeParams( DelegateName, Param1Type, Param2Type, Param3Type ) FUNC_DECLARE_DELEGATE( DelegateName, void, Param1Type, Param2Type, Param3Type )