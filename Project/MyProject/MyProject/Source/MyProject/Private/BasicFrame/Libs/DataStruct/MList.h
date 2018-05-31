#ifndef __MList_H
#define __MList_H

#include <vector>
// TODO:
//#include "Prequisites.h"	// TODO: 添加了这一样包含文件，导致 UiMgr.h  TMList<UiFormId> mTmpList; 这一行编译错误，凡是使用 TMList 的都会报错，递归包含导致的错误
#include "Ctx.h"
#include "LogSys.h"

#include "UtilStr.h"
#include "UtilContainers.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief 对系统 List 的封装
*/
template <typename T>
class MList
{
public:
	typedef typename std::vector<T>::iterator Ite;

protected:
	std::vector<T> mList;
	int mUniqueId;       // 唯一 Id ，调试使用

public:
	MList()
	{

	}

	MList(int capacity)
		: mList(capacity)
	{

	}

	~MList()
	{

	}

	std::vector<T>& getList()
	{
		return mList;
	}

	int getUniqueId()
	{
		return mUniqueId;
	}

	void setUniqueId(int value)
	{
		mUniqueId = value;
	}

	void add(T item)
	{
		mList.push_back(item);
	}

	bool remove(T item)
	{
		UtilVector::Remove(mList, item);
		return true;
	}

	T& operator [] (int index)
	{
		return mList[index];
	}

	void clear()
	{
		mList.clear();
	}

	int count()
	{
		return mList.size();
	}

	void removeAt(int index)
	{
		UtilVector::RemoveAt(mList, index);
	}

	int indexOf(T item)
	{
		return UtilVector::IndexOf(mList, item);
	}

	void insert(int index, T item)
	{
		if (index <= count())
		{
			UtilVector::Insert(mList, index, item);
		}
		else
		{
			GLogSys->log(UtilStr::Format("Insert Failed index={0}, Count={1}", index, count()));
		}
	}

	bool contains(T item)
	{
		return indexOf(item) != -1;
	}
};

MY_END_NAMESPACE

#endif