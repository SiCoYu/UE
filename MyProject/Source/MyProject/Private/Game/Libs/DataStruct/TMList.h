#ifndef __TMList_H
#define __TMList_H

#include <vector>
#include "Common.h"
#include "UtilStr.h"
#include "UtilContainers.h"

/**
* @brief 对系统 List 的封装
*/
template <typename T>
class TMList
{
public:
	typedef typename std::vector<T>::iterator Ite;

protected:
	std::vector<T> m_list;
	int m_uniqueId;       // 唯一 Id ，调试使用

public:
	TMList()
	{

	}

	TMList(int capacity)
		: m_list(capacity)
	{

	}

	~TMList()
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
			g_pLogSys->log(UtilStr::Format("Insert Failed index={0}, Count={1}", index, Count()));
		}
	}

	bool Contains(T item)
	{
		return IndexOf(item) != -1;
	}
};

//typedef TMList<int> IntTMList;

#endif