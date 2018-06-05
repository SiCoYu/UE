#pragma once

#include "GObject.h"
#include "EventDispatchDelegate.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 类似 EventDispatch ，CallFuncObjectBase 提供单一的函数回调，EventDispatch 过于复杂，会提供一个列表
 */
class CallFuncObjectBase : public GObject
{
	M_DECLARE_CLASS(CallFuncObjectBase, GObject)

protected:
	EventDispatchDelegate mHandle;

public:
	CallFuncObjectBase();

	virtual void init();
	virtual void dispose();
	virtual void clear();
	virtual bool isValid();

	virtual void setEventHandle(EventDispatchDelegate handle);
	virtual void clearEventHandle(EventDispatchDelegate handle);
	virtual void dispatchEvent(IDispatchObject* dispObj);
};

MY_END_NAMESPACE