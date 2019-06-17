#ifndef __CallOnceEventDispatch_H
#define __CallOnceEventDispatch_H

#include "EventDispatch.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

/**
 * @brief 一次事件分发，分发一次就清理
 */
class CallOnceEventDispatch : public EventDispatch
{
	M_DECLARE_CLASS(CallOnceEventDispatch, EventDispatch)

public:
	CallOnceEventDispatch();
	virtual void dispatchEvent(IDispatchObject* dispatchObject) override;
};

MY_END_NAMESPACE

#endif