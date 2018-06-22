#ifndef __PromiseEventDispatch_H
#define __PromiseEventDispatch_H

#include "EventDispatchDelegate.h"
#include "AddOnceEventDispatch.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 记录状态的事件分发，永远不会漏掉事件
 */
class PromiseEventDispatch : public AddOnceEventDispatch
{
	M_DECLARE_CLASS(PromiseEventDispatch, AddOnceEventDispatch)
	
protected:
	int mEventState;
	bool mIsValid;

public:
	PromiseEventDispatch();

	void setEventState(int value);
	void clearEventState();
	virtual void addEventHandle(
		EventDispatchDelegate handle
	) override;
};
	
MY_END_NAMESPACE

#endif