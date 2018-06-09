#ifndef __NetLogDevice_H
#define __NetLogDevice_H

#include "LogDeviceBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class NetLogDevice : public LogDeviceBase
{
public:
	NetLogDevice();
};

MY_END_NAMESPACE

#endif