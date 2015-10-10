#include "MyProject.h"
#include "MCircularBuffer.h"
#include "DynBufResizePolicy.h"
#include "BufferUtil.h"
#include "DynBuffer.h"
#include "ByteBuffer.h"

/**
 * @brief ���캯��
 */
MCircularBuffer::MCircularBuffer(size_t initCapacity, size_t maxCapacity)
{
	m_dynBuffer = new DynBuffer(initCapacity, maxCapacity);

	m_first = 0;
	m_last = 0;

	m_tmpBA = new ByteBuffer();
}

MCircularBuffer::~MCircularBuffer()
{
	delete m_dynBuffer;
	delete m_tmpBA;
}

uint32 MCircularBuffer::getFirst()
{
	return m_first;
}

uint32 MCircularBuffer::getLast()
{
	return m_last;
}

char* MCircularBuffer::getBuff()
{
	return m_dynBuffer->m_buff;
}

std::size_t MCircularBuffer::getSize()
{
	return m_dynBuffer->m_size;
}

void MCircularBuffer::setSize(std::size_t value)
{
	m_dynBuffer->setSize(value);
}

bool MCircularBuffer::isLinearized()
{
	if (this->getSize() == 0)
	{
		return true;
	}

	return m_first < m_last;
}

bool MCircularBuffer::empty()
{
	return m_dynBuffer->m_size == 0;
}

size_t MCircularBuffer::getCapacity()
{
	return m_dynBuffer->m_iCapacity;
}

bool MCircularBuffer::full()
{
	return this->getCapacity() == this->getSize();
}

void MCircularBuffer::clear()
{
	m_dynBuffer->m_size = 0;
	m_first = 0;
	m_last = 0;
}

void MCircularBuffer::linearize()
{
	if (this->empty())        // û������
	{
		return;
	}
	if (isLinearized())
	{
		return;
	}
	else
	{
		// �������������������ڴ�ռ���
		char* tmp = new char[m_last];
		BufferUtil::Copy(m_dynBuffer->m_buff, 0, tmp, 0, m_last);  // ����һ���ڴ�ռ��е����ݵ� tmp
		BufferUtil::Copy(m_dynBuffer->m_buff, m_first, m_dynBuffer->m_buff, 0, m_dynBuffer->m_iCapacity - m_first);  // ������һ�����ݵ� 0 ����λ��
		BufferUtil::Copy(tmp, 0, m_dynBuffer->m_buff, m_dynBuffer->m_iCapacity - m_first, m_last);      // �����ڶ������ݵ�������

		delete tmp;

		m_first = 0;
		m_last = this->getSize();
	}
}

void MCircularBuffer::setCapacity(std::size_t newCapacity)
{
	if (newCapacity == this->getCapacity())
	{
		return;
	}
	if (newCapacity < this->getSize())       // ���ܷ���ȵ�ǰ�Ѿ�ռ�еĿռ仹С�Ŀռ�
	{
		return;
	}
	char* tmpbuff = new char[newCapacity];   // �����µĿռ�
	if (isLinearized()) // �������һ���ڴ�ռ�
	{
		// �Ѿ������Կռ�����Ȼ�������ƶ������� 0 ��λ��
		BufferUtil::Copy(m_dynBuffer->m_buff, m_first, tmpbuff, 0, m_dynBuffer->m_size);
	}
	else    // ����������ڴ�ռ�
	{
		BufferUtil::Copy(m_dynBuffer->m_buff, m_first, tmpbuff, 0, m_dynBuffer->m_iCapacity - m_first);
		BufferUtil::Copy(m_dynBuffer->m_buff, 0, tmpbuff, m_dynBuffer->m_iCapacity - m_first, m_last);
	}

	m_first = 0;
	m_last = m_dynBuffer->m_size;
	m_dynBuffer->m_iCapacity = newCapacity;
	delete m_dynBuffer->m_buff;
	m_dynBuffer->m_buff = tmpbuff;
}

/**
*@brief �ܷ���� num ���ȵ�����
*/
bool MCircularBuffer::canAddData(uint32 num)
{
	if (m_dynBuffer->m_iCapacity - m_dynBuffer->m_size > num) // �˷�һ���ֽڣ����� >= ��ʹ�� > 
	{
		return true;
	}

	return false;
}

/**
*@brief ��洢��β�����һ������
*/
void MCircularBuffer::pushBackArr(char* items, uint32 start, std::size_t len)
{
	if (!canAddData(len)) // �洢�ռ����Ҫ��ʵ���������ٶ� 1
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(len + m_dynBuffer->m_size, m_dynBuffer->m_iCapacity, m_dynBuffer->m_iMaxCapacity);
		setCapacity(closeSize);
	}

	if (isLinearized())
	{
		if (len <= (m_dynBuffer->m_iCapacity - m_last))
		{
			BufferUtil::Copy(items, start, m_dynBuffer->m_buff, m_last, len);
		}
		else
		{
			BufferUtil::Copy(items, start, m_dynBuffer->m_buff, m_last, m_dynBuffer->m_iCapacity - m_last);
			BufferUtil::Copy(items, m_dynBuffer->m_iCapacity - m_last, m_dynBuffer->m_buff, 0, len - (m_dynBuffer->m_iCapacity - m_last));
		}
	}
	else
	{
		BufferUtil::Copy(items, start, m_dynBuffer->m_buff, m_last, len);
	}

	m_last += len;
	m_last %= m_dynBuffer->m_iCapacity;

	m_dynBuffer->m_size += len;
}

void MCircularBuffer::pushBackBA(ByteBuffer* bu)
{
	//pushBack(bu.dynBuff.buff, bu.position, bu.bytesAvailable);
	pushBackArr(bu->getDynBuff()->getBuff(), 0, bu->getLength());
}

/**
*@brief ��洢��ͷ�����һ������
*/
void MCircularBuffer::pushFrontArr(char* items, std::size_t len)
{
	if (!canAddData(len)) // �洢�ռ����Ҫ��ʵ���������ٶ� 1
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(len + m_dynBuffer->m_size, m_dynBuffer->m_iCapacity, m_dynBuffer->m_iMaxCapacity);
		setCapacity(closeSize);
	}

	if (isLinearized())
	{
		if (len <= m_first)
		{
			BufferUtil::Copy(items, 0, m_dynBuffer->m_buff, m_first - len, len);
		}
		else
		{
			BufferUtil::Copy(items, len - m_first, m_dynBuffer->m_buff, 0, m_first);
			BufferUtil::Copy(items, 0, m_dynBuffer->m_buff, m_dynBuffer->m_iCapacity - (len - m_first), len - m_first);
		}
	}
	else
	{
		BufferUtil::Copy(items, 0, m_dynBuffer->m_buff, m_first - len, len);
	}

	if (len <= m_first)
	{
		m_first -= len;
	}
	else
	{
		m_first = m_dynBuffer->m_iCapacity - (len - m_first);
	}
	m_dynBuffer->m_size += len;
}

/**
* @brief �� CB �ж�ȡ���ݣ����ҽ�����ɾ��
*/
void MCircularBuffer::popFrontBA(ByteBuffer* bytearray, std::size_t len)
{
	frontBA(bytearray, len);
	popFrontLen(len);
}

// �����ǻ�ȡ���ݣ�����ɾ��
void MCircularBuffer::frontBA(ByteBuffer* bytearray, std::size_t len)
{
	bytearray->clear();          // ��������Ϊ��ʼֵ
	if (m_dynBuffer->m_size >= len)          // ͷ��ռ�� 4 ���ֽ�
	{
		if (isLinearized())      // ��һ���������ڴ�
		{
			bytearray->writeBytes(m_dynBuffer->m_buff, m_first, len);
		}
		else if (m_dynBuffer->m_iCapacity - m_first >= len)
		{
			bytearray->writeBytes(m_dynBuffer->m_buff, m_first, len);
		}
		else
		{
			bytearray->writeBytes(m_dynBuffer->m_buff, m_first, m_dynBuffer->m_iCapacity - m_first);
			bytearray->writeBytes(m_dynBuffer->m_buff, 0, len - (m_dynBuffer->m_iCapacity - m_first));
		}
	}

	bytearray->setPos(0);        // �������ݶ�ȡ��ʼλ��
}

/**
* @brief �� CB ͷ��ɾ������
*/
void MCircularBuffer::popFrontLen(uint32 len)
{
	if (isLinearized())  // ��һ���������ڴ�
	{
		m_first += len;
	}
	else if (m_dynBuffer->m_iCapacity - m_first >= len)
	{
		m_first += len;
	}
	else
	{
		m_first = len - (m_dynBuffer->m_iCapacity - m_first);
	}

	m_dynBuffer->m_size -= len;
}

// ���Լ�β�����һ�� CirculeBuffer 
void MCircularBuffer::pushBackCB(MCircularBuffer* rhv)
{
	if (m_dynBuffer->m_iCapacity - m_dynBuffer->m_size < rhv->getSize())
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(rhv->getSize() + m_dynBuffer->m_size, m_dynBuffer->m_iCapacity, m_dynBuffer->m_iMaxCapacity);
		setCapacity(closeSize);
	}
	//this.m_size += rhv.size;
	//this.m_last = this.m_size;

	//m_tmpBA.clear();
	rhv->frontBA(m_tmpBA, rhv->getSize());
	pushBackBA(m_tmpBA);

	//if (rhv.isLinearized()) // �������һ���ڴ�ռ�
	//{
	//    Array.Copy(rhv.buff, rhv.first, m_buff, 0, rhv.size);
	//}
	//else    // ����������ڴ�ռ�
	//{
	//    Array.Copy(rhv.buff, rhv.first, m_buff, 0, rhv.capacity() - rhv.first);
	//    Array.Copy(m_buff, 0, m_buff, rhv.capacity() - rhv.first, rhv.last);
	//}
	//rhv.clear();
}