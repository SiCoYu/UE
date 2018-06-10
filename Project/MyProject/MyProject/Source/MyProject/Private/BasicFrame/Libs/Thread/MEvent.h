#ifndef __MEvent_H
#define __MEvent_H

#include "GObject.h"
#include "PlatformDefine.h"

class FEvent;

MY_BEGIN_NAMESPACE(MyNS)

class MEvent : public GObject
{
protected:
	FEvent* mEvent;

public:
	MEvent();
	~MEvent();

	void init();
	void dispose();

	void Wait();
	void Reset();
	void Set();
	void WaitOne();
};

MY_END_NAMESPACE

#endif