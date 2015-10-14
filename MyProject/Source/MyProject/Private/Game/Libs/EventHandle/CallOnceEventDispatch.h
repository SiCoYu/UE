#ifndef __CallOnceEventDispatch_H
#define __CallOnceEventDispatch_H

#include "EventDispatch.h"

/**
 * @brief 一次事件分发，分发一次就清理
 */
class CallOnceEventDispatch : public EventDispatch
{
    CallOnceEventDispatch()
    {

    }

	virtual void dispatchEvent(IDispatchObject dispatchObject) override
    {
        base.dispatchEvent(dispatchObject);
        clearEventHandle();
    }
};

#endif