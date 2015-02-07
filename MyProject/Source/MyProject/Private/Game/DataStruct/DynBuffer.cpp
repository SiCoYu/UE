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

std::size_t DynBuffer::size()
{
	return m_size;
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
	memcpy(tmpbuff, m_storage, m_iCapacity);
	m_iCapacity = newCapacity;

	delete[] m_storage;
	m_storage = tmpbuff;
}

void DynBuffer::push(char* pItem, std::size_t len)
{
	if (len > m_iCapacity)
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(len, capacity());
		setCapacity(closeSize);
	}

	memcpy(m_storage, pItem, len);
	m_size = len;
}