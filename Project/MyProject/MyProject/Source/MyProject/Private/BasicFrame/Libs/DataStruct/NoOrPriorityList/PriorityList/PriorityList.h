#pragma once

#include "GObject.h"
#include "INoOrPriorityList.h"
#include "MList.h"
#include "PrioritySort.h"
#include "MDictionary.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 优先级队列，外部一定不能直接引用 PriorityProcessObject 类型的对象，内部会管理 PriorityProcessObject 的生命周期
 */
class PriorityList : public GObject, public  INoOrPriorityList
{
protected:
	MList<PriorityProcessObject> mPriorityProcessObjectList;  // 优先级对象列表
    PrioritySort mPrioritySort;   // 排序方式

    MDictionary<INoOrPriorityObject, int> mDic;   // 查找字典
    bool mIsSpeedUpFind;          // 是否开启查找
    bool mIsOpKeepSort;           // 操作的时候是否保持排序

public:
	PriorityList()
    {
        this.mPriorityProcessObjectList = new MList<PriorityProcessObject>();
        this.mPrioritySort = PrioritySort.ePS_Great;
        this.mIsSpeedUpFind = false;
        this.mIsOpKeepSort = false;
    }

    void init()
    {

    }

    void dispose()
    {
        if(null != this.mPriorityProcessObjectList)
        {
            this.mPriorityProcessObjectList.dispose();
            this.mPriorityProcessObjectList = null;
        }
        if(null != this.mDic)
        {
            this.mDic.dispose();
            this.mDic = null;
        }
    }

    void setIsSpeedUpFind(bool value)
    {
        this.mIsSpeedUpFind = value;

        if (this.mIsSpeedUpFind)
        {
            this.mDic = new MDictionary<INoOrPriorityObject, int>();
        }
    }

    void setIsOpKeepSort(bool value)
    {
        this.mIsOpKeepSort = value;
    }

    void clear()
    {
        int index = 0;
        int listLen = this.count();

        while(index < listLen)
        {
            NumIdBufferObjectFactory.deleteObject(this.mPriorityProcessObjectList.get(index));
            this.mPriorityProcessObjectList.set(index, null);
            index += 1;
        }

        this.mPriorityProcessObjectList.clear();

        if(this.mIsSpeedUpFind)
        {
            this.mDic.clear();
        }
    }

    int count()
    {
        return this.mPriorityProcessObjectList.count();
    }

    INoOrPriorityObject get(int index)
    {
        INoOrPriorityObject ret = null;

        if(index < this.count())
        {
            ret = this.mPriorityProcessObjectList.get(index).mPriorityObject;
        }

        return ret;
    }

    float getPriority(int index)
    {
        float ret = 0;

        if (index < this.count())
        {
            ret = this.mPriorityProcessObjectList.get(index).mPriority;
        }

        return ret;
    }

    bool contains(INoOrPriorityObject item)
    {
        bool ret = false;

        if (null != item)
        {
            if (this.mIsSpeedUpFind)
            {
                ret = this.mDic.containsKey(item);
            }
            else
            {
                int index = 0;
                int listLen = this.mPriorityProcessObjectList.count();

                while (index < listLen)
                {
                    if (item == this.mPriorityProcessObjectList.get(index).mPriorityObject)
                    {
                        ret = true;
                        break;
                    }

                    ++index;
                }
            }
        }
        else
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("PriorityList::Contains, failed", LogTypeId.eLogPriorityListCheck);
            }
        }

        return ret;
    }

    void removeAt(int index)
    {
        PriorityProcessObject priorityProcessObject = null;
        priorityProcessObject = this.mPriorityProcessObjectList.get(index);

        if (this.mIsSpeedUpFind)
        {
            this._effectiveRemove(this.mPriorityProcessObjectList.get(index).mPriorityObject);
        }
        else
        {
            this.mPriorityProcessObjectList.removeAt(index);
        }

        if (null != priorityProcessObject)
        {
            NumIdBufferObjectFactory.deleteObject(priorityProcessObject);
            priorityProcessObject = null;
        }
    }

    int getIndexByPriority(float priority)
    {
        int retIndex = -1;

        int index = 0;
        int listLen = this.mPriorityProcessObjectList.count();

        while (index < listLen)
        {
            if (PrioritySort.ePS_Less == this.mPrioritySort)
            {
                if (this.mPriorityProcessObjectList.get(index).mPriority >= priority)
                {
                    retIndex = index;
                    break;
                }
            }
            else if (PrioritySort.ePS_Great == this.mPrioritySort)
            {
                if (this.mPriorityProcessObjectList.get(index).mPriority <= priority)
                {
                    retIndex = index;
                    break;
                }
            }

            ++index;
        }

        return retIndex;
    }

    int getIndexByPriorityObject(INoOrPriorityObject priorityObject)
    {
        int retIndex = -1;

        int index = 0;
        int listLen = this.mPriorityProcessObjectList.count();

        while (index < listLen)
        {
            if (this.mPriorityProcessObjectList.get(index).mPriorityObject == priorityObject)
            {
                retIndex = index;
                break;
            }

            ++index;
        }

        return retIndex;
    }

    int getIndexByNoOrPriorityObject(INoOrPriorityObject priorityObject)
    {
        return this.getIndexByPriorityObject(priorityObject);
    }

    void addPriorityObject(INoOrPriorityObject priorityObject, float priority = 0.0f)
    {
        if (null != priorityObject)
        {
            if (!this.contains(priorityObject))
            {
                PriorityProcessObject priorityProcessObject = null;
                //priorityProcessObject = new PriorityProcessObject();
                priorityProcessObject = NumIdBufferObjectFactory.newObject<PriorityProcessObject>(BufferType.eBT_PriorityProcessObject, true);

                priorityProcessObject.mPriorityObject = priorityObject;
                priorityProcessObject.mPriority = priority;

                if (!this.mIsOpKeepSort)
                {
                    this.mPriorityProcessObjectList.add(priorityProcessObject);

                    if (this.mIsSpeedUpFind)
                    {
                        this.mDic.add(priorityObject, this.mPriorityProcessObjectList.count() - 1);
                    }
                }
                else
                {
                    int index = this.getIndexByPriority(priority);

                    if (-1 == index)
                    {
                        this.mPriorityProcessObjectList.add(priorityProcessObject);

                        if (this.mIsSpeedUpFind)
                        {
                            this.mDic.add(priorityObject, this.mPriorityProcessObjectList.count() - 1);
                        }
                    }
                    else
                    {
                        this.mPriorityProcessObjectList.insert(index, priorityProcessObject);

                        if (this.mIsSpeedUpFind)
                        {
                            this.mDic.add(priorityObject, index);
                            this._updateIndex(index + 1);
                        }
                    }
                }
            }
        }
        else
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("PriorityList::addPriorityObject, failed", LogTypeId.eLogPriorityListCheck);
            }
        }
    }

    void removePriorityObject(INoOrPriorityObject priorityObject)
    {
        if (this.contains(priorityObject))
        {
            if (this.mIsSpeedUpFind)
            {
                this._effectiveRemove(priorityObject);
            }
            else
            {
                int index = this.getIndexByPriorityObject(priorityObject);

                if(-1 != index)
                {
                    this.mPriorityProcessObjectList.removeAt(index);
                }
            }
        }
    }

    public void addNoOrPriorityObject(INoOrPriorityObject noPriorityObject, float priority = 0.0f)
    {
        this.addPriorityObject(noPriorityObject, priority);
    }

    void removeNoOrPriorityObject(INoOrPriorityObject noPriorityObject)
    {
        this.removePriorityObject(noPriorityObject);
    }

    // 快速移除元素
protected:
	bool _effectiveRemove(INoOrPriorityObject item)
    {
        bool ret = false;

        if (this.mDic.containsKey(item))
        {
            ret = true;

            int index = this.mDic.value(item);
            this.mDic.remove(item);

            if (index == this.mPriorityProcessObjectList.count() - 1)    // 如果是最后一个元素，直接移除
            {
                this.mPriorityProcessObjectList.removeAt(index);
            }
            else
            {
                // 这样移除会使优先级顺序改变
                if (!this.mIsOpKeepSort)
                {
                    this.mPriorityProcessObjectList.set(index, this.mPriorityProcessObjectList.get(this.mPriorityProcessObjectList.count() - 1));
                    this.mPriorityProcessObjectList.removeAt(this.mPriorityProcessObjectList.count() - 1);
                    this.mDic.add(this.mPriorityProcessObjectList.get(index).mPriorityObject, index);
                }
                else
                {
                    this.mPriorityProcessObjectList.removeAt(index);
                    this._updateIndex(index);
                }
            }
        }

        return ret;
    }

    void _updateIndex(int index)
    {
        int listLen = this.mPriorityProcessObjectList.count();

        while (index < listLen)
        {
            this.mDic.add(this.mPriorityProcessObjectList.get(index).mPriorityObject, index);

            ++index;
        }
    }
};

MY_END_NAMESPACE