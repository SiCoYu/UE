#pragma once

/**
 * @brief 非优先级或者优先级列表
 */
class INoOrPriorityList
{
    void setIsSpeedUpFind(bool value);
    void setIsOpKeepSort(bool value);
    void init();
    void dispose();
    void clear();
    int count();

    INoOrPriorityObject get(int index);
    bool contains(INoOrPriorityObject item);
    void removeAt(int index);
    int getIndexByNoOrPriorityObject(INoOrPriorityObject priorityObject);

    void addNoOrPriorityObject(INoOrPriorityObject noPriorityObject, float priority = 0.0f);
    void removeNoOrPriorityObject(INoOrPriorityObject noPriorityObject);
};