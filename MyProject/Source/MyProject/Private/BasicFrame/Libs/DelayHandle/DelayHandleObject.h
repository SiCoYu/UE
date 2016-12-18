#ifndef __DelayHandleObject_H
#define __DelayHandleObject_H

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

#endif