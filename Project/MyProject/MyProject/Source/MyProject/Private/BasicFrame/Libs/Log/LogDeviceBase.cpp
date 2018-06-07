#include "MyProject.h"
#include "LogDeviceBase.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(LogDeviceBase, GObject)

LogDeviceBase::LogDeviceBase()
{
	this->mLogDeviceType = LogDeviceType::eWinLogDevice;
}

void LogDeviceBase::setLogDeviceType(LogDeviceType value)
{
	this->mLogDeviceType = value;
}

LogDeviceType LogDeviceBase::getLogDeviceType()
{
	return this->mLogDeviceType;
}

MY_END_NAMESPACE