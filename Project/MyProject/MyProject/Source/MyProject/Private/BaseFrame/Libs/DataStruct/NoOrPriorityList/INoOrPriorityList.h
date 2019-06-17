#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class INoOrPriorityObject;

/**
 * @brief 非优先级或者优先级列表
 */
class INoOrPriorityList
{
public:
    virtual void setIsSpeedUpFind(bool value) = 0;
	virtual void setIsOpKeepSort(bool value) = 0;
	virtual void init() = 0;
	virtual void dispose() = 0;
	virtual void clear() = 0;
	virtual int count() = 0;

	virtual INoOrPriorityObject* get(int index) = 0;
	virtual bool contains(INoOrPriorityObject* item) = 0;
	virtual void removeAt(int index) = 0;
	virtual int getIndexByNoOrPriorityObject(INoOrPriorityObject* priorityObject) = 0;

	virtual void addNoOrPriorityObject(INoOrPriorityObject* noPriorityObject, float priority = 0.0f) = 0;
	virtual void removeNoOrPriorityObject(INoOrPriorityObject* noPriorityObject) = 0;
};

MY_END_NAMESPACE