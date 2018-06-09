#pragma once

#include "DelayPriorityHandleMgr.h"
#include "ITickedObject.h"
#include "IDelayHandleItem.h"
#include "INoOrPriorityObject.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 每一帧执行的对象管理器
 */
class TickObjectPriorityMgr : public DelayPriorityHandleMgr, public ITickedObject, /*public IDelayHandleItem,*/ public INoOrPriorityObject
{
	M_DECLARE_CLASS(TickObjectPriorityMgr, DelayPriorityHandleMgr)

public:
	TickObjectPriorityMgr();

	virtual public void init() override;
	virtual public void dispose() override;
	void onTick(float delta, TickMode tickMode);
	virtual void advance(float delta, TickMode tickMode);
	virtual void _onPreAdvance(float delta, TickMode tickMode);
	virtual void _onExecAdvance(float delta, TickMode tickMode);
	virtual void _onPostAdvance(float delta, TickMode tickMode);
};

MY_END_NAMESPACE