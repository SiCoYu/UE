#include "MyProject.h"
#include "DelayHandleObject.h"
#include "IDelayHandleItem.h"
#include "DelayHandleParamBase.h"

MY_BEGIN_NAMESPACE(MyNS)

DelayHandleObject::DelayHandleObject()
	: mDelayObject(nullptr), mDelayParam(nullptr)
{

}

MY_END_NAMESPACE