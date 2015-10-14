#ifndef __TickProcessObject_H
#define __TickProcessObject_H

public class TickProcessObject
{
public:
	ITickedObject m_tickObject = null;
	float m_priority = 0.0f;

public:
	TickProcessObject();
}

#endif