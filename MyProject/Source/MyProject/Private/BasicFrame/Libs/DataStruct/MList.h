#ifndef __MList_H
#define __MList_H

#include <vector>
// TODO:
//#include "Common.h"	// TODO: 添加了这一样包含文件，导致 UIMgr.h  TMList<UIFormID> m_tmpList; 这一行编译错误，凡是使用 TMList 的都会报错，递归包含导致的错误
#include "Ctx.h"
#include "LogSys.h"

#include "UtilStr.h"
#include "UtilContainers.h"

/**
* @brief 对系统 List 的封装
*/
template <typename T>
class MList
{
public:
	typedef typename std::vector<T>::iterator Ite;

protected:
	std::vector<T> m_list;
	int m_uniqueId;       // 唯一 Id ，调试使用

public:
	MList()
	{

	}

	MList(int capacity)
		: m_list(capacity)
	{

	}

	~MList()
	{

	}

	std::vector<T>& getList()
	{
		return m_list;
	}

	int getUniqueId()
	{
		return m_uniqueId;
	}

	void setUniqueId(int value)
	{
		m_uniqueId = value;
	}

	void Add(T item)
	{
		m_list.push_back(item);
	}

	bool Remove(T item)
	{
		UtilVector::Remove(m_list, item);
		return true;
	}

	T& operator [] (int index)
	{
		return m_list[index];
	}

	void Clear()
	{
		m_list.clear();
	}

	int Count()
	{
		return m_list.size();
	}

	void RemoveAt(int index)
	{
		UtilVector::RemoveAt(m_list, index);
	}

	int IndexOf(T item)
	{
		return UtilVector::IndexOf(m_list, item);
	}

	void Insert(int index, T item)
	{
		if (index <= Count())
		{
			UtilVector::Insert(m_list, index, item);
		}
		else
		{
			GLogSys->log(UtilStr::Format("Insert Failed index={0}, Count={1}", index, Count()));
		}
	}

	bool Contains(T item)
	{
		return IndexOf(item) != -1;
	}
};

#endif