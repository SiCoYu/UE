#ifndef __TickProcessObject_H
#define __TickProcessObject_H

class ITickedObject;

class TickProcessObject
{
public:
	ITickedObject* mTickObject;
	float mPriority;

public:
	TickProcessObject();
};

#endif