#ifndef __TickProcessObject_H
#define __TickProcessObject_H

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ITickedObject;

class TickProcessObject : public GObject
{
public:
	ITickedObject* mTickObject;
	float mPriority;

public:
	TickProcessObject();
};

MY_END_NAMESPACE

#endif