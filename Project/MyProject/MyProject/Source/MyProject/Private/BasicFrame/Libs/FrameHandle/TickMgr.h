#ifndef __TickMgr_H
#define __TickMgr_H

#include "DelayHandleMgrBase.h"
#include "MList.h"
#include "BaseClassDef.h"

class TickProcessObject;
class ITickedObject;

/**
* @brief 心跳管理器
*/
class TickMgr : public DelayHandleMgrBase
{
	M_DECLARE_SUPER_KW(DelayHandleMgrBase)

protected:
	MList<TickProcessObject*> mTickList;

public:
	TickMgr();

public:
	virtual void init();
	virtual void dispose();

	void addTick(ITickedObject* tickObj, float priority = 0.0f);
	virtual void addObject(IDelayHandleItem* delayObject, float priority = 0.0f) override;
	virtual void delObject(IDelayHandleItem* delayObject) override;
	void Advance(float delta);
};

#endif