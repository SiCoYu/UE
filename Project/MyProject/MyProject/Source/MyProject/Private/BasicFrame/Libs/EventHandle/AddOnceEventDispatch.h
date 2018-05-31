#ifndef __AddOnceEventDispatch_H
#define __AddOnceEventDispatch_H

#include "EventDispatch.h"
#include "EventDispatchDelegate.h"
#include "BaseClassDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 事件回调函数只能添加一次
 */
class AddOnceEventDispatch : public EventDispatch
{
	M_DECLARE_SUPER_KW(EventDispatch)

public:
	AddOnceEventDispatch(int eventId_ = 0);
	virtual void addEventHandle(EventDispatchDelegate handle) override;
};

MY_END_NAMESPACE

#endif