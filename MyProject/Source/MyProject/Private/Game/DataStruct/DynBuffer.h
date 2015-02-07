#ifndef __DYNBUFFER_H
#define __DYNBUFFER_H

class DynBuffer
{
protected:
	char* m_storage;
	std::size_t m_size;
	std::size_t m_iCapacity;

public:
	std::size_t size();
	std::size_t capacity();
};

#endif			// __DYNBUFFER_H