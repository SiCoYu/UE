#ifndef __ScreenLogDevice_H
#define __ScreenLogDevice_H

#include "LogDeviceBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ScreenLogDevice : public LogDeviceBase
{
public:
	ScreenLogDevice();
};

MY_END_NAMESPACE

#endif