#pragma once

#include "IDispatchObject.h"
#include "PlatformDefine.h"

class UMyAnimInstanceBase;

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @动画相关操作
 */
class AnimController : public IDispatchObject
{
protected:
	UMyAnimInstanceBase* mAnimInstance;

public:
	AnimController();

public:
	void init();
	void dispose();
};

MY_END_NAMESPACE