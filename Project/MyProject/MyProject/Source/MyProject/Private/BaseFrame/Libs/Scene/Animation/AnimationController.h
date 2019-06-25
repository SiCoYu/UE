#pragma once

#include "IDispatchObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AnimController : public IDispatchObject
{
protected:
	

public:
	AnimController();

public:
	void init();
	void dispose();
};

MY_END_NAMESPACE