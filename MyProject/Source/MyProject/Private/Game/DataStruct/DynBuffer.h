#ifndef __DYNBUFFER_H
#define __DYNBUFFER_H

#include <cstddef>
#include "BufferDefaultValue.h"

/**
 * @brief 动态增长缓冲区，不分类型，就是 byte 缓冲区
 */
template <class T>
class DynBuffer
{
	friend class ClientBuffer;

protected:
	char* m_storage;
	std::size_t m_size;
	std::size_t m_iCapacity;
	std::size_t m_maxCapacity;

public:
	DynBuffer(size_t initCapacity = INITCAPACITY, size_t maxCapacity = MAXCAPACITY);
	~DynBuffer();
	std::size_t size();
	std::size_t capacity();
	std::size_t maxCapacity();
	void setCapacity(std::size_t newCapacity);
	void setSize(std::size_t len);
	char* getStorage();
	void push(char* pItem, std::size_t len);
};

#endif			// __DYNBUFFER_H