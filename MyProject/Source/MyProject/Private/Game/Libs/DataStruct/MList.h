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
    protected int m_uniqueId;       // 唯一 Id ，调试使用

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

#endif