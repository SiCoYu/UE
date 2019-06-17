#pragma once

#include "GObject.h"
#include "LogDeviceType.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class LogDeviceBase : public GObject
{
	M_DECLARE_CLASS(LogDeviceBase, GObject)

protected:
	LogDeviceType mLogDeviceType;

public:
	LogDeviceBase();

	void setLogDeviceType(LogDeviceType value);
	LogDeviceType getLogDeviceType();
};

MY_END_NAMESPACE