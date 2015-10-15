#ifndef __TickProcessObject_H
#define __TickProcessObject_H

class ITickedObject;

class TickProcessObject
{
public:
	ITickedObject* m_tickObject;
	float m_priority;

public:
	TickProcessObject();
};

#endif