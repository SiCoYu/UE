#ifndef __DYNBUFFER_H
#define __DYNBUFFER_H

#include "Platform.h"
#include <cstddef>
#include "BufferCV.h"
#include "DynBufResizePolicy.h"

/**
 * @brief 动态增长缓冲区，不分类型，就是 byte 缓冲区
 */
template <class T>
class DynBuffer
{
	friend class ClientBuffer;

public:
	std::size_t m_iCapacity;
	std::size_t m_iMaxCapacity;
	std::size_t m_size;
	T* m_buff;

public:
	DynBuffer(size_t initCapacity = BufferCV::INIT_CAPACITY, size_t maxCapacity = BufferCV::MAX_CAPACITY)
		: m_iCapacity(initCapacity), m_iMaxCapacity(maxCapacity)
	{
		m_size = 0;
		m_buff = new char[m_iCapacity];
	}

	~DynBuffer()
	{
		delete[] m_buff;
	}

	T* getBuff()
	{
		return m_buff;
	}

	void setBuff(char* value, uint32 len)
	{
		m_buff = value;
		m_iCapacity = len;
	}

	std::size_t getMaxCapacity()
	{
		return m_iMaxCapacity;
	}

	std::size_t getCapacity()
	{
		return m_iCapacity;
	}

	void setCapacity(std::size_t value)
	{
		if (value == m_iCapacity)
		{
			return;
		}
		if (value < this->getSize())       // 不能分配比当前已经占有的空间还小的空间
		{
			return;
		}

		char* tmpbuff = new char[value];   // 分配新的空间
		memcpy(tmpbuff, m_buff, m_iCapacity);

		delete[] m_buff;
		m_buff = tmpbuff;
		m_iCapacity = value;
	}

	std::size_t getSize()
	{
		return m_size;
	}

	void setSize(std::size_t value)
	{
		if (m_size > this->getCapacity())
		{
			extendDeltaCapicity(value - this->getSize());
		}

		m_size = value;
	}

	void extendDeltaCapicity(uint32 delta)
	{
		this->setCapacity(DynBufResizePolicy::getCloseSize(this->getSize() + delta, this->getCapacity(), this->getMaxCapacity()));
	}

	//void push(char* pItem, std::size_t len)
	//{
	//	if (len > m_iCapacity)
	//	{
	//		uint32 closeSize = DynBufResizePolicy::getCloseSize(len, this->getCapacity(), this->getMaxCapacity());
	//		setCapacity(closeSize);
	//	}
	//
	//	memcpy(m_buff, pItem, len);
	//	m_size = len;
	//}

	bool canAddData(uint32 num)
	{
		if (m_iCapacity - m_size >= num)
		{
			return true;
		}

		return false;
	}
};

#endif			// __DYNBUFFER_H