#ifndef __LockList_H
#define __LockList_H

#include "DynBuffer.h"
#include "MMutex.h"
#include "Platform.h"
#include <string>

/**
 * @brief 线程安全列表， T 是 Object ，便于使用 Equal 比较地址
 */
template <class T>
class LockList
{
protected:
	DynBuffer<T> m_dynamicBuffer;
    MMutex* m_visitMutex;
    T m_retItem;

public:
	LockList(std::string name, uint32 initCapacity = 32/*BufferCV.INIT_ELEM_CAPACITY*/, uint32 maxCapacity = 8 * 1024 * 1024/*BufferCV.MAX_CAPACITY*/);
	~LockList();

	uint32 getCount();
	T& operator[](int index);
	void Add(T item);
	bool Remove(T item);
	T RemoveAt(int index);
	int IndexOf(T item);
};

#endif