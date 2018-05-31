#pragma once

#include "MList.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief MIndexList ，元素是保存一个在列表中的索引的，减少 Key 比较，加快查找
 */
template <class T>
class MIndexList
{
protected:
	MList<T> mList;
    int mUniqueId;       // 唯一 Id ，调试使用
    int mEleTotal;       // 元素总数
    bool mIsOpKeepSort;           // 操作的时候是否保持排序

public:
	MIndexList()
    {
        this->mEleTotal = 0;
        this->mList = new List<T>();
        this->mIsOpKeepSort = false;
    }

    MIndexList(int capacity)
    {
        this->mList = new List<T>(capacity);
        this->mEleTotal = capacity;
    }

    void setIsOpKeepSort(bool value)
    {
        this->mIsOpKeepSort = value;
    }

    //T[] ToArray()
    //{
    //    return this->mList.ToArray();
    //}

    MList<T> list()
    {
        return this->mList;
    }

    int getUniqueId()
    {
        return this->mUniqueId;
    }

	void setUniqueId(int value)
    {
        this->mUniqueId = value;
    }

    int getSize()
    {
        // 频繁获取这个字段比较耗时
        //return this->mList.Count;
        return this->mEleTotal;
    }

    void add(T item)
    {
        this->mList.Add(item);
        this->mEleTotal += 1;
    }

    // 主要是 Add 一个 float 类型的 Vector3
    void add(T item_1, T item_2, T item_3)
    {
        this->add(item_1);
        this->add(item_2);
        this->add(item_3);
    }

    // 主要是 Add 一个 float 类型的 UV
    void add(T item_1, T item_2)
    {
        this->add(item_1);
        this->add(item_2);
    }

    // 主要是 Add 一个 byte 类型的 Color32
    void add(T item_1, T item_2, T item_3, T item_4)
    {
        this->add(item_1);
        this->add(item_2);
        this->add(item_3);
        this->add(item_4);
    }

    void push(T item)
    {
        this->add(item);
    }

    bool remove(T item)
    {
        return this->_effectiveRemove(item);
    }

    T& operator this[int index]
    {
        return this->mList[index];
    }

    T get(int index)
    {
        return this->mList[index];
    }

    void set(int index, T value)
    {
        if(nullptr != this->mList[index])
        {
            this->mList[index].resetIndex();
        }

        this->mList[index] = value;
        this->mList[index].setIndex(index);
    }

    void clear()
    {
        int index = 0;
        int listLen = this->mEleTotal;

        while(index < listLen)
        {
            this->mList[index].resetIndex();

            index += 1;
        }

        this->mList.Clear();
        this->mEleTotal = 0;
    }

    int count()
    {
        //return this->mList.Count;
        return this->mEleTotal;
    }

    void setLength(int value)
    {
        this->mList.Capacity = value;
    }

    void removeAt(int index)
    {
        if (index < this->count())
        {
            this->mList[index].resetIndex();
            this->mList.RemoveAt(index);
            this->mEleTotal -= 1;
        }
    }

    int indexOf(T item)
    {
        if(item.getIndex() < this->count())
        {
            return item.getIndex();
        }

        return -1;
    }

    void insert(int index, T item)
    {
        if (index <= this->count())
        {
            this->mList.Insert(index, item);
            item.setIndex(index);
            this->mEleTotal += 1;
            this->_updateIndex(index + 1);
        }
    }

    bool contains(T item)
    {
        return item.getIndex() != -1;
    }

    void sort(System.Comparison<T> comparer)
    {
        this->mList.Sort(comparer);
    }

    void merge(MList<T> appendList)
    {
        if(appendList != nullptr)
        {
            foreach(T item in appendList.list())
            {
                this->mList.Add(item);
                item.setIndex(this->mEleTotal);
                this->mEleTotal += 1;
            }
        }
    }

    // 快速移除元素
protected:
	bool _effectiveRemove(T item)
    {
        bool ret = false;

        int idx = item.getIndex();

        if (-1 != idx)
        {
            ret = true;

            if (idx == this->count() - 1)    // 如果是最后一个元素，直接移除
            {
                this->removeAt(idx);
            }
            else
            {
                if (!this->mIsOpKeepSort)
                {
                    this->mList[idx] = this->mList[this->count() - 1];
                    this->removeAt(this->count() - 1);
                }
                else
                {
                    this->removeAt(idx);
                    this->_updateIndex(idx);
                }
            }
        }

        return ret;
    }

    void _updateIndex(int idx)
    {
        int len = this->count();

        while(idx < len)
        {
            this->mList[idx].setIndex(idx);

            ++idx;
        }
    }
};

MY_END_NAMESPACE