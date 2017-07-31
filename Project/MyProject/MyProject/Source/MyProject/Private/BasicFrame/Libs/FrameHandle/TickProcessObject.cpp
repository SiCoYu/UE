#include "MyProject.h"
#include "TickProcessObject.h"
#include "ITickedObject.h"

TickProcessObject::TickProcessObject()
	: mTickObject(nullptr), mPriority(0.0f)
{

}