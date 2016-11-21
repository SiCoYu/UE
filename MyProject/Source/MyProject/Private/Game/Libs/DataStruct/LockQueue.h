#ifndef __LockQueue_H
#define __LockQueue_H

#include <string>
#include "LockList.h"

template <class T>
class LockQueue
{
protected:
	LockList<T> m_list;

public:
	LockQueue(std::string name)
		: m_list(name)
	{
		//m_list = new LockList<T>("name");
	}

	void push(T item)
	{
		m_list.Add(item);
	}

	T pop()
	{
		return m_list.RemoveAt(0);
	}
};

#endif