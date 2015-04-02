#include "MyProject.h"
#include "MStorageBuffer.h"
#include "DynBufResizePolicy.h"
#include <string.h>

MStorageBuffer::MStorageBuffer(std::size_t initCapacity, std::size_t maxCapacity)
	: m_size(0), m_iCapacity(initCapacity), m_maxCapacity(maxCapacity)
{
	m_storage = new char[m_iCapacity];
}

MStorageBuffer::~MStorageBuffer()
{
	delete[] m_storage;
}

void MStorageBuffer::setSize(std::size_t len)
{
	m_size = len;

	if (m_size > m_iCapacity)
	{
		setCapacity(m_size);
	}
}

void MStorageBuffer::setCapacity(std::size_t newCapacity)
{
	if (newCapacity > m_maxCapacity)
	{
		newCapacity = m_maxCapacity;
	}

	if (newCapacity <= m_size)       // 不能分配比当前已经占有的空间还小的空间
	{
		return;
	}

	if (newCapacity <= m_iCapacity)
	{
		return;
	}

	char* tmpbuff = new char[newCapacity];   // 分配新的空间
	memcpy(tmpbuff, m_storage, m_iCapacity);
	m_iCapacity = newCapacity;

	delete[] m_storage;
	m_storage = tmpbuff;
}

/**
*@brief 能否添加 num 长度的数据
*/
bool MStorageBuffer::canAddData(uint32 num)
{
	if (m_iCapacity - m_size >= num)
	{
		return true;
	}

	return false;
}