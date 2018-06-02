#ifndef __DelayAddParam_H
#define __DelayAddParam_H

#include "DelayHandleParamBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class DelayAddParam : public DelayHandleParamBase
{
public:
	float mPriority;

public:
	DelayAddParam();
};

MY_END_NAMESPACE

#endif