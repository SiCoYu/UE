#include "MyProject.h"
#include "DynBuffer.h"
#include "DynBufResizePolicy.h"
#include <string.h>

DynBuffer::DynBuffer()
	: m_iCapacity(INITCAPACITY)
{
	m_storage = new char[INITCAPACITY];
}

DynBuffer::~DynBuffer()
{
	delete[] m_storage;
}

size_t DynBuffer::capacity()
{
	return m_iCapacity;
}

void DynBuffer::setCapacity(std::size_t newCapacity)
{
	if (newCapacity <= capacity())
	{
		return;
	}

	char* tmpbuff = new char[newCapacity];   // 分配新的空间
	std::memcpy(tmpbuff, m_storage, m_iCapacity);
	m_iCapacity = newCapacity;

	delete[] m_storage;
	m_storage = tmpbuff;
}