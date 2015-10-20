#ifndef __MList_H
#define __MList_H

#include <vector>
#include "Common.h"
#include "UtilStr.h"
#include "UtilContainers.h"

/**
 * @brief 对系统 List 的封装
 */
template <class T>
class MList
{
public:
	typedef typename std::vector<T>::iterator Ite;

protected:
	std::vector<T> m_list;
	int m_uniqueId;       // 唯一 Id ，调试使用

public:
	MList();
	MList(int capacity);
	~MList();

	std::vector<T>& getList();
	int getUniqueId();
	void setUniqueId(int value);
	void Add(T item);
	bool Remove(T item);

	T& operator [] (int index);
	void Clear();
	int Count();
	void RemoveAt(int index);
	int IndexOf(T item);
	void Insert(int index, T item);
	bool Contains(T item);
};

template <class T>
MList<T>::MList()
{

}

template <class T>
MList<T>::MList(int capacity)
	: m_list(capacity)
{

}

template <class T>
MList<T>::~MList()
{

}

template <class T>
std::vector<T>& MList<T>::getList()
{
	return m_list;
}

template <class T>
int MList<T>::getUniqueId()
{
	return m_uniqueId;
}

template <class T>
void MList<T>::setUniqueId(int value)
{
	m_uniqueId = value;
}

template <class T>
void MList<T>::Add(T item)
{
	m_list.push_back(item);
}

template <class T>
bool MList<T>::Remove(T item)
{
	UtilVector::Remove(m_list, item);
	return true;
}

template <class T>
T& MList<T>::operator [] (int index)
{
	return m_list[index];
}

template <class T>
void MList<T>::Clear()
{
	m_list.clear();
}

template <class T>
int MList<T>::Count()
{
	return m_list.size();
}

template <class T>
void MList<T>::RemoveAt(int index)
{
	UtilVector::RemoveAt(m_list, index);
}

template <class T>
int MList<T>::IndexOf(T item)
{
	return UtilVector::IndexOf(m_list, item);
}

template <class T>
void MList<T>::Insert(int index, T item)
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

template <class T>
bool MList<T>::Contains(T item)
{
	return IndexOf(item) != -1;
}

#endif