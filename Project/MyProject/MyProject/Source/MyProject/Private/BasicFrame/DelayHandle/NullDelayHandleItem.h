#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 默认的接口实现
 */
public class NullDelayHandleItem : IDelayHandleItem
{
public:
	void setClientDispose(bool isDispose)
	{

	}

	bool isClientDispose()
	{
		return false;
	}
}

MY_END_NAMESPACE