#pragma once.

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 优先级队列对象
 */
class PriorityProcessObject : public GObject
{
public:
	INoOrPriorityObject mPriorityObject;
    float mPriority;

public:
	PriorityProcessObject()
    {
        this.onPutInPool();
    }

    void putInPool()
    {
        this.onPutInPool();
    }

    void getFromPool()
    {
        this.onGetFromPool();
    }

    void dispose()
    {
        this.onPutInPool();
    }

    void setIsUsePool(bool value)
    {
        this.mIsUsePool = value;
    }

	bool isUsePool()
    {
        return this.mIsUsePool;
    }

    void onPutInPool()
    {
        this.mPriorityObject = null;
        this.mPriority = 0.0f;
    }

    void onGetFromPool()
    {

    }

    int getBufferType()
    {
        return (int)BufferType.eBT_PriorityProcessObject;
    }
};

MY_END_NAMESPACE