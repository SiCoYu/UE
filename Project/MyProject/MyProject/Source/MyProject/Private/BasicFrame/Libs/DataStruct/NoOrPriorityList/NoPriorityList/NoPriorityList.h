#pragma once

#include "INoOrPriorityList.h"
#include "MList.h"
#include "MDictionary.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class INoOrPriorityObject;

/**
 * @brief 优先级队列，注意并不是继承 GContainerObject ，而是继承 GObject ，只有基本数据结构才继承 GContainerObject ，例如 MList , MDictionary
 */
class NoPriorityList : public GObject, public INoOrPriorityList
{
protected:
	MList<INoOrPriorityObject*> mNoPriorityProcessObjectList;  // 优先级对象列表

    MDictionary<INoOrPriorityObject*, int> mDic;       // 查找字典
    bool mIsSpeedUpFind;      // 是否开启查找

public:
	NoPriorityList();
	
    void init();
    void dispose();
    void setIsSpeedUpFind(bool value);
    void setIsOpKeepSort(bool value);
    void clear();
    int count();
    INoOrPriorityObject* get(int index);
    bool contains(INoOrPriorityObject* item);
    void removeAt(int index);

    int getIndexByNoPriorityObject(INoOrPriorityObject* priorityObject);
    int getIndexByNoOrPriorityObject(INoOrPriorityObject* priorityObject);
    void addNoPriorityObject(INoOrPriorityObject* noPriorityObject);
    void removeNoPriorityObject(INoOrPriorityObject* noPriorityObject);
    void addNoOrPriorityObject(INoOrPriorityObject* noPriorityObject, float priority = 0.0f);
    void removeNoOrPriorityObject(INoOrPriorityObject* noPriorityObject);

protected:
    // 快速移除元素
    bool _effectiveRemove(INoOrPriorityObject* item);
    void _updateIndex(int idx);
};

MY_END_NAMESPACE