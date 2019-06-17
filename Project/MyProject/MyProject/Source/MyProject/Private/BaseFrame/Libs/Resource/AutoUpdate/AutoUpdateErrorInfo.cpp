#include "MyProject.h"
#include "AutoUpdateErrorInfo.h"

MY_BEGIN_NAMESPACE(MyNS)

AutoUpdateErrorInfo::AutoUpdateErrorInfo()
{
	this->mAutoUpdateErrorCode = AutoUpdateErrorCode::eErrorNo;
	this->mAutoUpdateErrorDesc = "";
}

AutoUpdateErrorCode AutoUpdateErrorInfo::getErrorCode()
{
	return this->mAutoUpdateErrorCode;
}

void AutoUpdateErrorInfo::setErrorCode(AutoUpdateErrorCode value)
{
	this->mAutoUpdateErrorCode = value;
}

MY_END_NAMESPACE