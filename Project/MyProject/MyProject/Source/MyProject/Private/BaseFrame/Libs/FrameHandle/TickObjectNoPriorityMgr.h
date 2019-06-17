#pragma once

#include "DelayNoPriorityHandleMgr.h"
#include "ITickedObject.h"
#include "IDelayHandleItem.h"
#include "INoOrPriorityObject.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

// 每一帧执行的对象管理器
class TickObjectNoPriorityMgr : public DelayNoPriorityHandleMgr/*, public ITickedObject*//*, public IDelayHandleItem*//*, public INoOrPriorityObject*/
{
	M_DECLARE_CLASS(TickObjectNoPriorityMgr, DelayNoPriorityHandleMgr)

public:
	TickObjectNoPriorityMgr();

	virtual void init() override;
	virtual void dispose() override;
	void onTick(float delta, TickMode tickMode);
	virtual void _onPreAdvance(float delta, TickMode tickMode);
	virtual void _onExecAdvance(float delta, TickMode tickMode);
	virtual void _onPostAdvance(float delta, TickMode tickMode);
};

MY_END_NAMESPACE