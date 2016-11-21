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
	LockList(std::string name, uint32 initCapacity = 32/*BufferCV.INIT_ELEM_CAPACITY*/, uint32 maxCapacity = 8 * 1024 * 1024/*BufferCV.MAX_CAPACITY*/)
		: m_dynamicBuffer(initCapacity, maxCapacity)
	{
		//m_dynamicBuffer = new DynBuffer<T>(initCapacity, maxCapacity);
		m_visitMutex = new MMutex();
	}

	~LockList()
	{
		delete m_visitMutex;
	}

	uint32 getCount()
	{
		MLock mlock(m_visitMutex);
		{
			return m_dynamicBuffer.m_size;
		}
	}

	T& operator[](int index)
	{
		MLock mlock(m_visitMutex);
		{
			if (index < m_dynamicBuffer.m_size)
			{
				return m_dynamicBuffer.m_buff[index];
			}
			else
			{
				return m_retItem;
			}
		}
	}

	void Add(T item)
	{
		MLock mlock(m_visitMutex);
		{
			if (m_dynamicBuffer.m_size >= m_dynamicBuffer.m_iCapacity)
			{
				m_dynamicBuffer.extendDeltaCapicity(1);
			}

			m_dynamicBuffer.m_buff[m_dynamicBuffer.m_size] = item;
			++m_dynamicBuffer.m_size;
		}
	}

	bool Remove(T item)
	{
		MLock mlock(m_visitMutex);
		{
			int idx = 0;
			foreach(var elem in m_dynamicBuffer.m_buff)
			{
				if (item.Equals(elem))       // 地址比较
				{
					this.RemoveAt(idx);
					return true;
				}

				++idx;
			}
			return false;
		}
	}

	T RemoveAt(int index)
	{
		MLock mlock(m_visitMutex);
		{
			if (index < m_dynamicBuffer.m_size)
			{
				m_retItem = m_dynamicBuffer.m_buff[index];

				if (index < m_dynamicBuffer.m_size)
				{
					if (index != m_dynamicBuffer.m_size - 1 && 1 != m_dynamicBuffer.m_size) // 如果删除不是最后一个元素或者总共就大于一个元素
					{
						Array.Copy(m_dynamicBuffer.m_buff, index + 1, m_dynamicBuffer.m_buff, index, m_dynamicBuffer.m_size - 1 - index);
					}

					--m_dynamicBuffer.m_size;
				}
			}
			else
			{
				m_retItem = default(T);
			}

			return m_retItem;
		}
	}

	int IndexOf(T item)
	{
		MLock mlock(m_visitMutex);
		{
			int idx = 0;
			foreach(var elem in m_dynamicBuffer.m_buff)
			{
				if (item.Equals(elem))       // 地址比较
				{
					this.RemoveAt(idx);
					return idx;
				}

				++idx;
			}
			return -1;
		}
	}
};

#endif