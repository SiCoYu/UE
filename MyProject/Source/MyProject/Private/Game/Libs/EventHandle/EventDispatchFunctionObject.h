#ifndef __EventDispatchFunctionObject_H
#define __EventDispatchFunctionObject_H

#include "IDelayHandleItem.h"

class EventDispatchFunctionObject : public IDelayHandleItem
{
public:
	bool m_bClientDispose;       // 是否释放了资源
    Action<IDispatchObject> m_handle;

    EventDispatchFunctionObject()
    {
        m_bClientDispose = false;
    }

    void setClientDispose()
    {
        m_bClientDispose = true;
    }

    bool getClientDispose()
    {
        return m_bClientDispose;
    }
};

#endif