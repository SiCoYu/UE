#pragma once

#include "CallFuncObjectBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

class CallFuncObjectFixParam : public CallFuncObjectBase
{
	M_DECLARE_CLASS(CallFuncObjectFixParam, CallFuncObjectBase)

public:
	CallFuncObjectFixParam();
};

MY_END_NAMESPACE