#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 优先级队列对象
 */
class PriorityProcessObject : public GObject
{
public:
	INoOrPriorityObject* mPriorityObject;
    float mPriority;

public:
	PriorityProcessObject();

    void putInPool();
    void getFromPool();
    void dispose();
    void setIsUsePool(bool value);
	bool isUsePool();
    void onPutInPool();
    void onGetFromPool();
    int getBufferType();
};

MY_END_NAMESPACE