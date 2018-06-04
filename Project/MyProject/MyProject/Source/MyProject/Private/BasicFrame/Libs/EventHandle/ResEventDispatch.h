#ifndef __ResEventDispatch_H
#define __ResEventDispatch_H

#include "EventDispatch.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

class ResEventDispatch : public EventDispatch
{
	M_DECLARE_CLASS(ResEventDispatch, EventDispatch)

public:
	ResEventDispatch();
	virtual ~ResEventDispatch();
	virtual void dispatchEvent(IDispatchObject* dispatchObject) override;
};

MY_END_NAMESPACE

#endif