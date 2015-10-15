#include "MyProject.h"
#include "LockList.h"

template <class T>
LockList<T>::LockList(std::string name, uint32 initCapacity, uint32 maxCapacity)
{
	m_dynamicBuffer = new DynBuffer<T>(initCapacity, maxCapacity);
	m_visitMutex = new MMutex();
}

template <class T>
LockList<T>::~LockList()
{
	delete m_visitMutex;
}

template <class T>
uint32 LockList<T>::getCount()
{
	MLock mlock(m_visitMutex);
	{
		return m_dynamicBuffer.m_size;
	}
}

template <class T>
T& LockList<T>::operator[](int index)
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

template <class T>
void LockList<T>::Add(T item)
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

template <class T>
bool LockList<T>::Remove(T item)
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

template <class T>
T LockList<T>::RemoveAt(int index)
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

template <class T>
int LockList<T>::IndexOf(T item)
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