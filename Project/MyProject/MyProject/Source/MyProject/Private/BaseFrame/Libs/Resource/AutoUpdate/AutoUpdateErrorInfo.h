#pragma once

#include <string>
#include "GObject.h"
#include "AutoUpdateErrorCode.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 自动更新错误原因
 */
class AutoUpdateErrorInfo : public GObject
{
protected:
	AutoUpdateErrorCode mAutoUpdateErrorCode;
    std::string mAutoUpdateErrorDesc;

public:
	AutoUpdateErrorInfo();

	AutoUpdateErrorCode getErrorCode();
	void setErrorCode(AutoUpdateErrorCode value);
};

MY_END_NAMESPACE