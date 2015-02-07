#ifndef __DYNBUFFER_H
#define __DYNBUFFER_H

#include <cstddef>

class DynBuffer
{
protected:
	char* m_storage;
	std::size_t m_iCapacity;

public:
	DynBuffer();
	~DynBuffer();
	std::size_t capacity();
	void setCapacity(std::size_t newCapacity);
};

#endif			// __DYNBUFFER_H