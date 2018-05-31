#ifndef __ResEventDispatch_H
#define __ResEventDispatch_H

#include "EventDispatch.h"
#include "BaseClassDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

class ResEventDispatch : public EventDispatch
{
	M_DECLARE_SUPER_KW(EventDispatch)

public:
	ResEventDispatch();
	virtual ~ResEventDispatch();
	virtual void dispatchEvent(IDispatchObject* dispatchObject) override;
};

MY_END_NAMESPACE

#endif