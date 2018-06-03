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
	MKeyIndexList();

	void clear();
	MList<TValue> getList();
	TValue get(int index);
	MDictionary<TKey, TValue> getIndexDic();
	void add(TKey key, TValue value);
	void addToFirst(TKey key, TValue value);
	void addToSecond(TKey key, TValue value);
	void remove(TKey key);
	TValue getAndRemoveByKey(TKey key);
	TValue value(TKey key);
	int count();
	bool containsKey(TKey key);
};

MY_END_NAMESPACE

#include "MIndexList.inl"