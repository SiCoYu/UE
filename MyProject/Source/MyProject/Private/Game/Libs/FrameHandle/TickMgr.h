#ifndef __TickMgr_H
#define __TickMgr_H

#include "DelayHandleMgrBase.h"
#include "MList.h"

class TickProcessObject;
class ITickedObject;

/**
* @brief 心跳管理器
*/
class TickMgr : public DelayHandleMgrBase
{
protected:
	MList<TickProcessObject*> m_tickLst;

public:
	TickMgr();
	void addTick(ITickedObject* tickObj, float priority = 0.0f);
	virtual void addObject(IDelayHandleItem* delayObject, float priority = 0.0f) override;
	virtual void delObject(IDelayHandleItem* delayObject) override;
	void Advance(float delta);
};

#endif