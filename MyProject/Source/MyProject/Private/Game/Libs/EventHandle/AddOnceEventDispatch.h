#ifndef __AddOnceEventDispatch_H
#define __AddOnceEventDispatch_H

#include "EventDispatch.h"

/**
 * @brief 事件回调函数只能添加一次
 */
class AddOnceEventDispatch : public EventDispatch
{
public:
    AddOnceEventDispatch(int eventId_ = 0)
        : base(eventId_)
    {

    }

	virtual void addEventHandle(Action<IDispatchObject> handle) override
    {
        // 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
        if (!existEventHandle(handle))
        {
            base.addEventHandle(handle);
        }
    }
};

#endif