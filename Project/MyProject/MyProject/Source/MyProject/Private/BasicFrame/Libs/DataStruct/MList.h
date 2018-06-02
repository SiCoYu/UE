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

	void add(T item)
	{
		this->mList.push_back(item);
	}

	bool remove(T item)
	{
		UtilVector::Remove(this->mList, item);
		return true;
	}

	T& operator [] (int index)
	{
		return this->mList[index];
	}

	void clear()
	{
		this->mList.clear();
	}

	int count()
	{
		return this->mList.size();
	}

	void remove(T& item)
	{
		int index = this->indexOf(item);

		if (-1 != index)
		{
			this.removeAt(index);
		}
	}

	void removeAt(int index)
	{
		UtilVector::RemoveAt(this->mList, index);
	}

	int indexOf(T item)
	{
		return UtilVector::IndexOf(this->mList, item);
	}

	void insert(int index, T item)
	{
		if (index <= this->count())
		{
			UtilVector::Insert(this->mList, index, item);
		}
		else
		{
			GLogSys->log(UtilStr::Format("Insert Failed index={0}, Count={1}", index, this->count()));
		}
	}

	bool contains(T item)
	{
		return this->indexOf(item) != -1;
	}
};

MY_END_NAMESPACE

#endif