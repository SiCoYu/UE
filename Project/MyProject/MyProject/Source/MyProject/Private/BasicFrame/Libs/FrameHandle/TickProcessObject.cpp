#include "MyProject.h"
#include "TickProcessObject.h"
#include "ITickedObject.h"

MY_BEGIN_NAMESPACE(MyNS)

TickProcessObject::TickProcessObject()
	: mTickObject(nullptr), mPriority(0.0f)
{

}

MY_END_NAMESPACE