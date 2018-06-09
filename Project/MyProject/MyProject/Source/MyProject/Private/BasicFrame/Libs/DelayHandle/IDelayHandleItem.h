#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 延迟添加的对象
 */
class IDelayHandleItem
{
public:
	IDelayHandleItem() {};
	virtual ~IDelayHandleItem() {};
};

MY_END_NAMESPACE