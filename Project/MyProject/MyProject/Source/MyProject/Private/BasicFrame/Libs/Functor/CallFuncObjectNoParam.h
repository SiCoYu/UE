#pragma once

#include "CallFuncObjectBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class CallFuncObjectNoParam : public CallFuncObjectBase
{
	M_DECLARE_CLASS(CallFuncObjectNoParam, CallFuncObjectBase)

public:
	CallFuncObjectNoParam();
};

MY_END_NAMESPACE