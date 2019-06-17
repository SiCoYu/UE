#ifndef __FileLogDevice_H
#define __FileLogDevice_H

#include "LogDeviceBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class FileLogDevice : public LogDeviceBase
{
public:
	FileLogDevice();
};

MY_END_NAMESPACE

#endif