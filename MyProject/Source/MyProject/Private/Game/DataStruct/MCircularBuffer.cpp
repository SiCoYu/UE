#include "MyProject.h"
#include "MCircularBuffer.h"
#include "DynBufResizePolicy.h"
#include <string.h>

/**
 * @brief 构造函数
 */
MCircularBuffe::MCircularBuffer() 
	: m_head(0), m_tail(0), m_size(0), m_iCapacity(0)
{
	m_storage = new char[INITCAPACITY];
}

MCircularBuffe::~MCircularBuffer()
{
	delete[] m_storage;
}

std::size_t MCircularBuffer::size()
{
	return m_size;
}

bool MCircularBuffer::full()
{
	return (m_iCapacity == m_size);
}

bool MCircularBuffer::empty()
{
	return (m_size == 0);
}

void MCircularBuffer::linearize()
{

}

bool MCircularBuffer::isLinearized()
{
	return m_head <= m_tail;
}

size_t MCircularBuffer::capacity()
{
	return m_iCapacity;
}

void MCircularBuffer::setCapacity(std::size_t newCapacity)
{
	if (newCapacity == capacity())
	{
		return;
	}
	if (newCapacity < size())       // 不能分配比当前已经占有的空间还小的空间
	{
		return;
	}
	char[] tmpbuff = new char[newCapacity];   // 分配新的空间
	if (isLinearized()) // 如果是在一段内存空间
	{
		std::memcpy(tmpbuff, m_storage + m_first, m_size);
	}
	else    // 如果在两端内存空间
	{
		std::memcpy(tmpbuff, m_storage + m_first, m_iCapacity - m_first);
		std::memcpy(tmpbuff + m_iCapacity - m_first, m_storage, m_tail);
	}

	m_first = 0;
	m_tail = m_size;
	m_iCapacity = newCapacity;

	delete[] m_storage;
	m_storage = tmpbuff;
}

/**
*@brief 能否添加 num 长度的数据
*/
bool MCircularBuffer::canAddData(uint num)
{
	if (m_iCapacity - m_size > num)
	{
		return true;
	}

	return false;
}

/**
* @brief 在缓冲区尾部添加
*/
void MCircularBuffer::pushBack(char* pItem, std::size_t startPos, std::size_t len)
{
	if (!canAddData(len)) // 存储空间必须要比实际数据至少多 1
	{
		uint closeSize = DynBufResizePolicy::getCloseSize(len + this.m_size, m_iCapacity);
		setCapacity(closeSize);
	}

	if (isLinearized())
	{
		if (len <= (m_iCapacity - m_tail))
		{
			std::memcpy(m_storage + m_tail, pItem + startPos, len);
		}
		else
		{
			std::memcpy(m_storage + m_tail, pItem + startPos, m_iCapacity - m_tail);
			std::memcpy(m_storage + 0, pItem + m_iCapacity - m_tail, len - (m_iCapacity - m_tail));
		}
	}
	else
	{
		std::memcpy(m_storage + m_tail, pItem + startPos, len);
	}

	m_tail += len;
	m_tail %= m_iCapacity;

	m_size += len;
}

/**
* @brief 在缓冲区头部添加
*/
bool MCircularBuffer::pushFront(char* pItem, std::size_t startPos, std::size_t len)
{
	if (!canAddData(len)) // 存储空间必须要比实际数据至少多 1
	{
		uint closeSize = DynBufResizePolicy::getCloseSize(len + this.m_size, m_iCapacity);
		setCapacity(closeSize);
	}

	if (isLinearized())
	{
		if (len <= m_first)
		{
			std::memcpy(m_storage + m_first - len, pItem + startPos, len);
		}
		else
		{
			std::memcpy(m_storage + 0, pItem + startPos + len - m_first, m_first);
			std::memcpy(m_storage + m_iCapacity - (len - m_first), pItem + 0, len - m_first);
		}
	}
	else
	{
		std::memcpy(m_storage + m_first - len, pItem + startPos + 0, len);
	}

	if (len <= m_first)
	{
		m_first -= (uint)len;
	}
	else
	{
		m_first = m_iCapacity - ((uint)len - m_first);
	}
	m_size += (uint)len;
}

/**
* @brief 获取缓冲区尾部，并且删除
*/
bool MCircularBuffer::popBack(char* pItem, std::size_t startPos, std::size_t len)
{
	if (back(pItem, startPos, len))
	{
		popBackLenNoData(len);
	}
}

/**
* @brief 获取缓冲区尾部，但是不删除
*/
char MCircularBuffer::back(char* pItem, std::size_t startPos, std::size_t len)
{
	if (len <= size())
	{
		return false;
	}

	if (isLinearized())
	{
		std::memcpy(pItem + startPos, m_storage + m_tail - len, len);
	}
	else
	{
		if (len <= m_tail)
		{
			std::memcpy(pItem + startPos, m_storage, len);
		}
		else
		{
			std::memcpy(pItem + startPos, m_storage + m_iCapacity - (len - m_tail), len - m_tail);
			std::memcpy(pItem + startPos + len - m_tail, m_storage + 0, m_tail);
		}
	}
}

void MCircularBuffer::popBackLenNoData(std::size_t len)
{
	m_tail -= len;
	m_tail += m_iCapacity;
	m_tail %= m_iCapacity;
	m_size -= len;
}

/**
* @brief 获取缓冲区头部，但是删除
*/
bool MCircularBuffer::popFront(char* pItem, std::size_t startPos, std::size_t len)
{
	if (front(pItem, startPos, len))
	{
		popFrontLenNoData(len);
	}
}

/**
* @brief 获取缓冲区头部，但是不删除
*/
char MCircularBuffer::front(char* pItem, std::size_t startPos, std::size_t len)
{
	if (len <= size())
	{
		return false;
	}

	if (isLinearized())
	{
		std::memcpy(pItem + startPos, m_storage + m_head, len);
	}
	else
	{
		if (len <= (m_iCapacity - m_head))
		{
			std::memcpy(pItem + startPos, m_storage + m_head, len);
		}
		else
		{
			std::memcpy(pItem + startPos, m_storage + m_head, m_iCapacity - m_head);
			std::memcpy(pItem + startPos + m_iCapacity - m_head, m_storage + 0, len - (m_iCapacity - m_head));
		}
	}
}

void MCircularBuffer::popFrontLenNoData(std::size_t len)
{
	m_head += len;
	m_head %= m_iCapacity;
	m_size -= len;
}