#pragma once

#include "GObject.h"
#include "INoOrPriorityList.h"
#include "MList.h"
#include "PrioritySort.h"
#include "MDictionary.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class INoOrPriorityObject;

/**
 * @brief 优先级队列，外部一定不能直接引用 PriorityProcessObject 类型的对象，内部会管理 PriorityProcessObject 的生命周期
 */
class PriorityList : public GObject, public  INoOrPriorityList
{
protected:
	MList<PriorityProcessObject*> mPriorityProcessObjectList;  // 优先级对象列表
    PrioritySort mPrioritySort;   // 排序方式

    MDictionary<INoOrPriorityObject*, int> mDic;   // 查找字典
    bool mIsSpeedUpFind;          // 是否开启查找
    bool mIsOpKeepSort;           // 操作的时候是否保持排序

public:
	PriorityList();

    void init();
    void dispose();
    void setIsSpeedUpFind(bool value);
    void setIsOpKeepSort(bool value);
    void clear();
    int count();
    INoOrPriorityObject get(int index);
    float getPriority(int index);
    bool contains(INoOrPriorityObject* item);
    void removeAt(int index);
    int getIndexByPriority(float priority);
    int getIndexByPriorityObject(INoOrPriorityObject* priorityObject);
    int getIndexByNoOrPriorityObject(INoOrPriorityObject* priorityObject);
    void addPriorityObject(INoOrPriorityObject* priorityObject, float priority = 0.0f);
    void removePriorityObject(INoOrPriorityObject* priorityObject);
    void addNoOrPriorityObject(INoOrPriorityObject* noPriorityObject, float priority = 0.0f);
    void removeNoOrPriorityObject(INoOrPriorityObject* noPriorityObject);
    // 快速移除元素
protected:
	bool _effectiveRemove(INoOrPriorityObject* item);
    void _updateIndex(int index);
};

MY_END_NAMESPACE