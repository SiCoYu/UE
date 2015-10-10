#ifndef __MEVENT_H
#define __MEVENT_H

class FEvent;

class MEvent
{
protected:
	FEvent* m_event;

public:
	MEvent();
	~MEvent();

	void Wait();
	void Reset();
	void Set();
	void WaitOne();
};

#endif