#ifndef __IDelayHandleItem_H
#define __IDelayHandleItem_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 延迟添加的对象
 */
class IDelayHandleItem
{
public:
	virtual void setClientDispose() = 0;
    virtual bool isClientDispose() = 0;
};

MY_END_NAMESPACE

#endif