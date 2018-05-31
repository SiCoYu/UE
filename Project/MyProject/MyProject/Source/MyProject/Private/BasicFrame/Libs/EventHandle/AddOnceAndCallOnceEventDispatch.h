#ifndef __AddOnceAndCallOnceEventDispatch_H
#define __AddOnceAndCallOnceEventDispatch_H

#include "EventDispatch.h"
#include "EventDispatchDelegate.h"
#include "BaseClassDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceAndCallOnceEventDispatch : public EventDispatch
{
	M_DECLARE_SUPER_KW(EventDispatch)

public:
	virtual void addEventHandle(EventDispatchDelegate handle) override;
	virtual void dispatchEvent(IDispatchObject* dispatchObject) override;
};

MY_END_NAMESPACE

#endif