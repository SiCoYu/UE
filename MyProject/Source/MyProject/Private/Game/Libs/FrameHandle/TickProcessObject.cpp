#include "MyProject.h"
#include "TickProcessObject.h"
#include "ITickedObject.h"

TickProcessObject::TickProcessObject()
	: m_tickObject(nullptr), m_priority(0.0f)
{

}