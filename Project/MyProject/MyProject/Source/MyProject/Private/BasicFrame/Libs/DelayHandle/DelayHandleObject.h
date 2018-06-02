#ifndef __DelayHandleObject_H
#define __DelayHandleObject_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDelayHandleItem;
class DelayHandleParamBase;

class DelayHandleObject
{
public:
	IDelayHandleItem* mDelayObject;
    DelayHandleParamBase* mDelayParam;

public:
	DelayHandleObject();
};

MY_END_NAMESPACE

#endif