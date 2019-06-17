#ifndef __IDelayTask_H
#define __IDelayTask_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDelayTask
{
public:
	virtual void delayExec() = 0;
};

MY_END_NAMESPACE

#endif