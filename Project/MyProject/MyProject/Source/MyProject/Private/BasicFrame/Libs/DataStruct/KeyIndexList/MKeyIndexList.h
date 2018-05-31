#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 通过 Key 索引的列表
 */
template <class TKey, class TValue>
class MKeyIndexList
{
protected:
	MList<TValue> mList;              // 数据列表
    MDictionary<TKey, TValue> mIndexDic;   // Key 字典

public:
	MKeyIndexList()
    {
        this.mList = new MList<TValue>();
        this.mList.setIsSpeedUpFind(true);
        this.mList.setIsOpKeepSort(true);

        this.mIndexDic = new MDictionary<TKey, TValue>();
    }

    void clear()
    {
        this.mList.clear();
        this.mIndexDic.clear();
    }

    MList<TValue> getList()
    {
        return this.mList;
    }

    TValue get(int index)
    {
        return this.mList.get(index);
    }

    MDictionary<TKey, TValue> getIndexDic()
    {
        return this.mIndexDic;
    }

    void add(TKey key, TValue value)
    {
        if(!this.mIndexDic.containsKey(key))
        {
            this.mList.add(value);
            this.mIndexDic.add(key, value);
        }
    }

    void addToFirst(TKey key, TValue value)
    {
        this.mList.insert(0, value);
        this.mIndexDic.add(key, value);
    }

    void addToSecond(TKey key, TValue value)
    {
        this.mList.insert(1, value);
        this.mIndexDic.add(key, value);
    }

    void remove(TKey key)
    {
        if(this.mIndexDic.containsKey(key))
        {
            this.mList.remove(this.mIndexDic.value(key));
            this.mIndexDic.remove(key);
        }
    }

    TValue getAndRemoveByKey(TKey key)
    {
        TValue item = this.value(key);
        this.remove(key);
        return item;
    }

    TValue value(TKey key)
    {
        TValue ret = nullptr;

        if(this.mIndexDic.containsKey(key))
        {
            ret = this.mIndexDic.value(key);
        }

        return ret;
    }

    int count()
    {
        return this.mList.count();
    }

    bool containsKey(TKey key)
    {
        return this.mIndexDic.containsKey(key);
    }
};

MY_END_NAMESPACE