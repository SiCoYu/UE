#pragma once

#include <string>
#include "AutoUpdateErrorCode.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 自动更新错误原因
 */
class AutoUpdateErrorInfo
{
protected:
	AutoUpdateErrorCode mAutoUpdateErrorCode;
    std::string mAutoUpdateErrorDesc;

public:
	AutoUpdateErrorInfo()
    {
        this->mAutoUpdateErrorCode = AutoUpdateErrorCode.eErrorNo;
        this->mAutoUpdateErrorDesc = "";
    }

    AutoUpdateErrorCode getErrorCode()
    {
        return this->mAutoUpdateErrorCode;
    }

    void setErrorCode(AutoUpdateErrorCode value)
    {
        this->mAutoUpdateErrorCode = value;
    }
};

MY_END_NAMESPACE