#include "MyProject.h"
#include "MCircularBuffer.h"
#include "DynBufResizePolicy.h"
#include <string.h>

/**
 * @brief ���캯��
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
	if (newCapacity < size())       // ���ܷ���ȵ�ǰ�Ѿ�ռ�еĿռ仹С�Ŀռ�
	{
		return;
	}
	char[] tmpbuff = new char[newCapacity];   // �����µĿռ�
	if (isLinearized()) // �������һ���ڴ�ռ�
	{
		std::memcpy(tmpbuff, m_storage + m_first, m_size);
	}
	else    // ����������ڴ�ռ�
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
*@brief �ܷ���� num ���ȵ�����
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
* @brief �ڻ�����β�����
*/
void MCircularBuffer::pushBack(char* pItem, std::size_t startPos, std::size_t len)
{
	if (!canAddData(len)) // �洢�ռ����Ҫ��ʵ���������ٶ� 1
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
* @brief �ڻ�����ͷ�����
*/
bool MCircularBuffer::pushFront(char* pItem, std::size_t startPos, std::size_t len)
{
	if (!canAddData(len)) // �洢�ռ����Ҫ��ʵ���������ٶ� 1
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
* @brief ��ȡ������β��������ɾ��
*/
bool MCircularBuffer::popBack(char* pItem, std::size_t startPos, std::size_t len)
{
	if (back(pItem, startPos, len))
	{
		popBackLenNoData(len);
	}
}

/**
* @brief ��ȡ������β�������ǲ�ɾ��
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
* @brief ��ȡ������ͷ��������ɾ��
*/
bool MCircularBuffer::popFront(char* pItem, std::size_t startPos, std::size_t len)
{
	if (front(pItem, startPos, len))
	{
		popFrontLenNoData(len);
	}
}

/**
* @brief ��ȡ������ͷ�������ǲ�ɾ��
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