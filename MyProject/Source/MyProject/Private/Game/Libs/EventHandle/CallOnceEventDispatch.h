#ifndef __CallOnceEventDispatch_H
#define __CallOnceEventDispatch_H

#include "EventDispatch.h"

class IDispatchObject;

/**
 * @brief 一次事件分发，分发一次就清理
 */
class CallOnceEventDispatch : public EventDispatch
{
public:
	CallOnceEventDispatch();
	virtual void dispatchEvent(IDispatchObject* dispatchObject) override;
};

#endif