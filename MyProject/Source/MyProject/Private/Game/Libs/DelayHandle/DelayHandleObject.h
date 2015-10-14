#ifndef __DelayHandleObject_H
#define __DelayHandleObject_H

class IDelayHandleItem;
class DelayHandleParamBase;

class DelayHandleObject
{
public:
	IDelayHandleItem* m_delayObject;
    DelayHandleParamBase* m_delayParam;

public:
	DelayHandleObject();
};

#endif