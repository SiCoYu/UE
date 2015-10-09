#ifndef __DYNBUFFER_H
#define __DYNBUFFER_H

#include "MyProject.h"
#include <cstddef>
#include "BufferDefaultValue.h"

/**
 * @brief 动态增长缓冲区，不分类型，就是 byte 缓冲区
 */
class DynBuffer
{
	friend class ClientBuffer;

public:
	std::size_t m_iCapacity;
	std::size_t m_iMaxCapacity;
	std::size_t m_size;
	char* m_buff;

public:
	DynBuffer(size_t initCapacity = INITCAPACITY, size_t maxCapacity = MAXCAPACITY);
	~DynBuffer();

	char* getBuff();
	void setBuff(char* value, uint32 len);

	std::size_t getMaxCapacity();
	std::size_t getCapacity();
	void setCapacity(std::size_t value);
	std::size_t getSize();
	void setSize(std::size_t value);

	void extendDeltaCapicity(uint32 delta);
	//void push(char* pItem, std::size_t len);
	bool canAddData(uint32 num);
};

#endif			// __DYNBUFFER_H