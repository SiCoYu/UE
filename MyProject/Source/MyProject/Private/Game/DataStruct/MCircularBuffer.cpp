#include "MyProject.h"
#include "MCircularBuffer.h"
#include "DynBufResizePolicy.h"
#include "BufferUtil.h"
#include "DynBuffer.h"
#include "ByteBuffer.h"

/**
 * @brief 构造函数
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
	if (this->empty())        // 没有数据
	{
		return;
	}
	if (isLinearized())
	{
		return;
	}
	else
	{
		// 数据在两个不连续的内存空间中
		char* tmp = new char[m_last];
		BufferUtil::Copy(m_dynBuffer->m_buff, 0, tmp, 0, m_last);  // 拷贝一段内存空间中的数据到 tmp
		BufferUtil::Copy(m_dynBuffer->m_buff, m_first, m_dynBuffer->m_buff, 0, m_dynBuffer->m_iCapacity - m_first);  // 拷贝第一段数据到 0 索引位置
		BufferUtil::Copy(tmp, 0, m_dynBuffer->m_buff, m_dynBuffer->m_iCapacity - m_first, m_last);      // 拷贝第二段数据到缓冲区

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
	if (newCapacity < this->getSize())       // 不能分配比当前已经占有的空间还小的空间
	{
		return;
	}
	char* tmpbuff = new char[newCapacity];   // 分配新的空间
	if (isLinearized()) // 如果是在一段内存空间
	{
		// 已经是线性空间了仍然将数据移动到索引 0 的位置
		BufferUtil::Copy(m_dynBuffer->m_buff, m_first, tmpbuff, 0, m_dynBuffer->m_size);
	}
	else    // 如果在两端内存空间
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
*@brief 能否添加 num 长度的数据
*/
bool MCircularBuffer::canAddData(uint32 num)
{
	if (m_dynBuffer->m_iCapacity - m_dynBuffer->m_size > num) // 浪费一个字节，不用 >= ，使用 > 
	{
		return true;
	}

	return false;
}

/**
*@brief 向存储空尾部添加一段内容
*/
void MCircularBuffer::pushBackArr(char* items, uint32 start, std::size_t len)
{
	if (!canAddData(len)) // 存储空间必须要比实际数据至少多 1
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
*@brief 向存储空头部添加一段内容
*/
void MCircularBuffer::pushFrontArr(char* items, std::size_t len)
{
	if (!canAddData(len)) // 存储空间必须要比实际数据至少多 1
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
* @brief 从 CB 中读取内容，并且将数据删除
*/
void MCircularBuffer::popFrontBA(ByteBuffer* bytearray, std::size_t len)
{
	frontBA(bytearray, len);
	popFrontLen(len);
}

// 仅仅是获取数据，并不删除
void MCircularBuffer::frontBA(ByteBuffer* bytearray, std::size_t len)
{
	bytearray->clear();          // 设置数据为初始值
	if (m_dynBuffer->m_size >= len)          // 头部占据 4 个字节
	{
		if (isLinearized())      // 在一段连续的内存
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

	bytearray->setPos(0);        // 设置数据读取起始位置
}

/**
* @brief 从 CB 头部删除数据
*/
void MCircularBuffer::popFrontLen(uint32 len)
{
	if (isLinearized())  // 在一段连续的内存
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

// 向自己尾部添加一个 CirculeBuffer 
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

	//if (rhv.isLinearized()) // 如果是在一段内存空间
	//{
	//    Array.Copy(rhv.buff, rhv.first, m_buff, 0, rhv.size);
	//}
	//else    // 如果在两端内存空间
	//{
	//    Array.Copy(rhv.buff, rhv.first, m_buff, 0, rhv.capacity() - rhv.first);
	//    Array.Copy(m_buff, 0, m_buff, rhv.capacity() - rhv.first, rhv.last);
	//}
	//rhv.clear();
}