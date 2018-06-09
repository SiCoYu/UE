#pragma once

#include "MClassInfo.h"
#include "MClassMacros.h"
#include "GObject.h"
#include "IDelayHandleItem.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 默认的接口实现
 */
class NullDelayHandleItem : public GObject/*, public IDelayHandleItem*/
{
	M_DECLARE_CLASS(NullDelayHandleItem, GObject)
};

MY_END_NAMESPACE