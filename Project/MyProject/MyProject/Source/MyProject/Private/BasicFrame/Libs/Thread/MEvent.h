#ifndef __MEVENT_H
#define __MEVENT_H

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