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
	LockQueue(std::string name);
	void push(T item);
	T pop();
};

#include "LockQueue.inl"

#endif