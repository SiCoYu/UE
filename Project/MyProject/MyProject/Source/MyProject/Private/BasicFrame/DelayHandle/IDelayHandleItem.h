#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 延迟添加的对象
 */
class IDelayHandleItem
{
	virtual void setClientDispose(bool isDispose) = 0;
	virtual bool isClientDispose() = 0;
}

MY_END_NAMESPACE