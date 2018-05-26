#ifndef __MEvent_H
#define __MEvent_H

#include "GObject.h"

class FEvent;

class MEvent : public GObject
{
protected:
	FEvent* mEvent;

public:
	MEvent();
	~MEvent();

	void Wait();
	void Reset();
	void Set();
	void WaitOne();
};

#endif