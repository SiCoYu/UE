#ifndef __TickMgr_H
#define __TickMgr_H

#include "TickObjectPriorityMgr.h"
#include "MList.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TickProcessObject;
class ITickedObject;

/**
* @brief 心跳管理器
*/
class TickMgr : public TickObjectPriorityMgr
{
	M_DECLARE_CLASS(TickMgr, TickObjectPriorityMgr)

protected:
	MList<TickProcessObject*> mTickList;

public:
	TickMgr();
	virtual ~TickMgr();

public:
	virtual void init();
	virtual void dispose();
	void addTick(ITickedObject* tickObj, float priority = 0.0f);
	void removeTick(ITickedObject* tickObj);
	void advance(float delta, TickMode tickMode);

protected:
	virtual void _addObject(IDelayHandleItem* delayObject, float priority = 0.0f) override;
	virtual void _removeObject(IDelayHandleItem* delayObject) override;

};

MY_END_NAMESPACE

#endif