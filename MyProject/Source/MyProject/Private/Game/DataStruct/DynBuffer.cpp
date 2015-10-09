#include "DynBuffer.h"
#include "DynBufResizePolicy.h"
#include <string.h>

DynBuffer::DynBuffer(size_t initCapacity, size_t maxCapacity)
	: m_iCapacity(initCapacity), m_iMaxCapacity(maxCapacity)
{
	m_size = 0;
	m_buff = new char[m_iCapacity];
}

DynBuffer::~DynBuffer()
{
	delete[] m_buff;
}

char* DynBuffer::getBuff()
{
	return m_buff;
}

void DynBuffer::setBuff(char* value, uint32 len)
{
	m_buff = value;
	m_iCapacity = len;
}

std::size_t DynBuffer::getMaxCapacity()
{
	return m_iMaxCapacity;
}

size_t DynBuffer::getCapacity()
{
	return m_iCapacity;
}

void DynBuffer::setCapacity(std::size_t value)
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

std::size_t DynBuffer::getSize()
{
	return m_size;
}

void DynBuffer::setSize(std::size_t value)
{
	if (m_size > this->getCapacity())
	{
		extendDeltaCapicity(value - this->getSize());
	}

	m_size = value;
}

//void DynBuffer::push(char* pItem, std::size_t len)
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

void DynBuffer::extendDeltaCapicity(uint32 delta)
{
	this->setCapacity(DynBufResizePolicy::getCloseSize(this->getSize() + delta, this->getCapacity(), this->getMaxCapacity()));
}

/**
*@brief 能否添加 num 长度的数据
*/
bool DynBuffer::canAddData(uint32 num)
{
	if (m_iCapacity - m_size >= num)
	{
		return true;
	}

	return false;
}