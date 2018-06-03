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
    MIndexList(int capacity)
	
    void setIsOpKeepSort(bool value);

    //T[] ToArray()
    //{
    //    return this->mList.ToArray();
    //}

    MList<T> getList();

    int getUniqueId();
	void setUniqueId(int value);
    void add(T item);
    // 主要是 Add 一个 float 类型的 Vector3
    void add(T item_1, T item_2, T item_3);
    // 主要是 Add 一个 float 类型的 UV
    void add(T item_1, T item_2);
    // 主要是 Add 一个 byte 类型的 Color32
    void add(T item_1, T item_2, T item_3, T item_4);
    bool remove(T item);
    T& operator[] (int index);
    T get(int index);
    void set(int index, T value);
    void clear();
    int count();
    void setLength(int value);
    void removeAt(int index);
    int indexOf(T item);
    void insert(int index, T item);
    bool contains(T item);
    //void sort(System.Comparison<T> comparer);
    //void merge(MList<T> appendList);

    // 快速移除元素
protected:
	bool _effectiveRemove(T item);
    void _updateIndex(int idx);
};

MY_END_NAMESPACE

#include "MIndexList.inl"