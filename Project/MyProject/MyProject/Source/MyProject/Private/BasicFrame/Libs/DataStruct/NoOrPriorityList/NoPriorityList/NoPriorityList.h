#pragma once

#include "GObject.h"
#include "INoOrPriorityList.h"
#include "MList.h"
#include "MDictionary.h"

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 优先级队列
 */
class NoPriorityList : public GObject, public INoOrPriorityList
{
protected:
	MList<INoOrPriorityObject*> mNoPriorityProcessObjectList;  // 优先级对象列表

    MDictionary<INoOrPriorityObject*, int> mDic;       // 查找字典
    bool mIsSpeedUpFind;      // 是否开启查找

public:
	NoPriorityList()
    {
        //this.mNoPriorityProcessObjectList = new MList<INoOrPriorityObject>();
        this.mIsSpeedUpFind = false;
    }

    void init()
    {

    }

    void dispose()
    {
        if(nullptr != this.mNoPriorityProcessObjectList)
        {
            this.mNoPriorityProcessObjectList.dispose();
            this.mNoPriorityProcessObjectList = nullptr;
        }
        if (nullptr != this.mDic)
        {
            this.mDic.dispose();
            this.mDic = nullptr;
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

    }

    void clear()
    {
        this.mNoPriorityProcessObjectList.clear();

        if(this.mIsSpeedUpFind)
        {
            this.mDic.clear();
        }
    }

    int count()
    {
        return this.mNoPriorityProcessObjectList.count();
    }

    INoOrPriorityObject get(int index)
    {
        INoOrPriorityObject ret = nullptr;

        if(index < this.count())
        {
            ret = this.mNoPriorityProcessObjectList.get(index);
        }

        return ret;
    }

    bool contains(INoOrPriorityObject item)
    {
        bool ret = false;

        if (nullptr != item)
        {
            if (this.mIsSpeedUpFind)
            {
                ret = this.mDic.containsKey(item);
            }
            else
            {
                int index = 0;
                int listLen = this.mNoPriorityProcessObjectList.count();

                while (index < listLen)
                {
                    if (item == this.mNoPriorityProcessObjectList.get(index))
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
                Ctx.msInstance.mLogSys.log("NoPriorityList::Contains, failed", LogTypeId.eLogNoPriorityListCheck);
            }
        }

        return ret;
    }

    void removeAt(int index)
    {
        if (this.mIsSpeedUpFind)
        {
            this._effectiveRemove(this.mNoPriorityProcessObjectList[index]);
        }
        else
        {
            this.mNoPriorityProcessObjectList.removeAt(index);
        }
    }

    int getIndexByNoPriorityObject(INoOrPriorityObject priorityObject)
    {
        int retIndex = -1;

        int index = 0;
        int listLen = this.mNoPriorityProcessObjectList.count();

        while (index < listLen)
        {
            if (this.mNoPriorityProcessObjectList.get(index) == priorityObject)
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
        return this.getIndexByNoPriorityObject(priorityObject);
    }

    void addNoPriorityObject(INoOrPriorityObject noPriorityObject)
    {
        if (nullptr != noPriorityObject)
        {
            if (!this.contains(noPriorityObject))
            {
                this.mNoPriorityProcessObjectList.add(noPriorityObject);

                if (this.mIsSpeedUpFind)
                {
                    this.mDic.add(noPriorityObject, this.mNoPriorityProcessObjectList.count() - 1);
                }
            }
        }
        else
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("NoPriorityList::addNoPriorityObject, failed", LogTypeId.eLogNoPriorityListCheck);
            }
        }
    }

    void removeNoPriorityObject(INoOrPriorityObject noPriorityObject)
    {
        if (nullptr != noPriorityObject)
        {
            if (this.contains(noPriorityObject))
            {
                if (this.mIsSpeedUpFind)
                {
                    this._effectiveRemove(noPriorityObject);
                }
                else
                {
                    int index = this.getIndexByNoPriorityObject(noPriorityObject);

                    if (-1 != index)
                    {
                        this.mNoPriorityProcessObjectList.removeAt(index);
                    }
                }
            }
        }
        else
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("NoPriorityList::addNoPriorityObject, failed", LogTypeId.eLogNoPriorityListCheck);
            }
        }
    }

    void addNoOrPriorityObject(INoOrPriorityObject noPriorityObject, float priority = 0.0f)
    {
        this.addNoPriorityObject(noPriorityObject);
    }

    public void removeNoOrPriorityObject(INoOrPriorityObject noPriorityObject)
    {
        this.removeNoPriorityObject(noPriorityObject);
    }

protected:
    // 快速移除元素
    bool _effectiveRemove(INoOrPriorityObject item)
    {
        bool ret = false;

        if (this.mDic.containsKey(item))
        {
            ret = true;

            int idx = this.mDic[item];
            this.mDic.remove(item);

            if (idx == this.mNoPriorityProcessObjectList.count() - 1)    // 如果是最后一个元素，直接移除
            {
                this.mNoPriorityProcessObjectList.removeAt(idx);
            }
            else
            {
                this.mNoPriorityProcessObjectList.set(idx, this.mNoPriorityProcessObjectList.get(this.mNoPriorityProcessObjectList.count() - 1));
                this.mNoPriorityProcessObjectList.removeAt(this.mNoPriorityProcessObjectList.count() - 1);
                this.mDic.add(this.mNoPriorityProcessObjectList.get(idx), idx);
            }
        }

        return ret;
    }

    void _updateIndex(int idx)
    {
        int listLen = this.mNoPriorityProcessObjectList.count();

        while (idx < listLen)
        {
            this.mDic.add(this.mNoPriorityProcessObjectList.get(idx), idx);

            ++idx;
        }
    }
};

MY_END_NAMESPACE