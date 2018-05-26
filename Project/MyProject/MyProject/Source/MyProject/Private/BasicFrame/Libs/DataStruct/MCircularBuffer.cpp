#include "MyProject.h"
#include "MCircularBuffer.h"
#include "DynBufResizePolicy.h"
#include "Array.h"
#include "MByteBuffer.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"

/**
 * @brief 构造函数
 */
MCircularBuffer::MCircularBuffer(
	size_t initCapacity, 
	size_t maxCapacity
)
{
	this->mDynBuffer = MY_NEW DynBuffer<char>(initCapacity, maxCapacity);

	this->mFirst = 0;
	this->mLast = 0;

	this->mTmpBA = MY_NEW MByteBuffer();
}

MCircularBuffer::~MCircularBuffer()
{
	MY_DELETE this->mDynBuffer;
	MY_DELETE this->mTmpBA;
}

uint32 MCircularBuffer::getFirst()
{
	return this->mFirst;
}

uint32 MCircularBuffer::getLast()
{
	return this->mLast;
}

char* MCircularBuffer::getBuffer()
{
	return this->mDynBuffer->mBuffer;
}

std::size_t MCircularBuffer::getSize()
{
	return this->mDynBuffer->mSize;
}

void MCircularBuffer::setSize(std::size_t value)
{
	this->mDynBuffer->setSize(value);
}

bool MCircularBuffer::isLinearized()
{
	if (this->getSize() == 0)
	{
		return true;
	}

	return this->mFirst < this->mLast;
}

bool MCircularBuffer::empty()
{
	return this->mDynBuffer->mSize == 0;
}

size_t MCircularBuffer::getCapacity()
{
	return this->mDynBuffer->mCapacity;
}

bool MCircularBuffer::full()
{
	return this->getCapacity() == this->getSize();
}

void MCircularBuffer::clear()
{
	this->mDynBuffer->mSize = 0;
	this->mFirst = 0;
	this->mLast = 0;
}

void MCircularBuffer::linearize()
{
	if (this->empty())        // 没有数据
	{
		return;
	}
	if (this->isLinearized())
	{
		return;
	}
	else
	{
		// 数据在两个不连续的内存空间中
		char* tmp = MY_NEW char[this->mLast];
		Array::Copy(this->mDynBuffer->mBuffer, 0, tmp, 0, mLast);  // 拷贝一段内存空间中的数据到 tmp
		Array::Copy(this->mDynBuffer->mBuffer, this->mFirst, this->mDynBuffer->mBuffer, 0, this->mDynBuffer->mCapacity - mFirst);  // 拷贝第一段数据到 0 索引位置
		Array::Copy(tmp, 0, this->mDynBuffer->mBuffer, this->mDynBuffer->mCapacity - this->mFirst, this->mLast);      // 拷贝第二段数据到缓冲区

		MY_DELETE tmp;

		this->mFirst = 0;
		this->mLast = this->getSize();
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

	char* tmpbuff = MY_NEW char[newCapacity];   // 分配新的空间

	if (this->isLinearized()) // 如果是在一段内存空间
	{
		// 已经是线性空间了仍然将数据移动到索引 0 的位置
		Array::Copy(this->mDynBuffer->mBuffer, this->mFirst, tmpbuff, 0, this->mDynBuffer->mSize);
	}
	else    // 如果在两端内存空间
	{
		Array::Copy(this->mDynBuffer->mBuffer, this->mFirst, tmpbuff, 0, this->mDynBuffer->mCapacity - this->mFirst);
		Array::Copy(this->mDynBuffer->mBuffer, 0, tmpbuff, this->mDynBuffer->mCapacity - this->mFirst, this->mLast);
	}

	this->mFirst = 0;
	this->mLast = this->mDynBuffer->mSize;
	this->mDynBuffer->mCapacity = newCapacity;

	MY_DELETE this->mDynBuffer->mBuffer;
	this->mDynBuffer->mBuffer = tmpbuff;
}

/**
*@brief 能否添加 num 长度的数据
*/
bool MCircularBuffer::canAddData(uint32 num)
{
	if (this->mDynBuffer->mCapacity - this->mDynBuffer->mSize > num) // 浪费一个字节，不用 >= ，使用 > 
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
	if (!this->canAddData(len)) // 存储空间必须要比实际数据至少多 1
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(len + this->mDynBuffer->mSize, this->mDynBuffer->mCapacity, this->mDynBuffer->mMaxCapacity);
		this->setCapacity(closeSize);
	}

	if (this->isLinearized())
	{
		if (len <= (this->mDynBuffer->mCapacity - this->mLast))
		{
			Array::Copy(items, start, this->mDynBuffer->mBuffer, this->mLast, len);
		}
		else
		{
			Array::Copy(items, start, this->mDynBuffer->mBuffer, this->mLast, this->mDynBuffer->mCapacity - this->mLast);
			Array::Copy(items, this->mDynBuffer->mCapacity - this->mLast, this->mDynBuffer->mBuffer, 0, len - (this->mDynBuffer->mCapacity - this->mLast));
		}
	}
	else
	{
		Array::Copy(items, start, this->mDynBuffer->mBuffer, this->mLast, len);
	}

	this->mLast += len;
	this->mLast %= mDynBuffer->mCapacity;

	this->mDynBuffer->mSize += len;
}

void MCircularBuffer::pushBackBA(MByteBuffer* bu)
{
	//pushBack(bu.dynBuff.buff, bu.position, bu.bytesAvailable);
	this->pushBackArr(bu->getDynBuffer()->getBuffer(), 0, bu->getLength());
}

/**
*@brief 向存储空头部添加一段内容
*/
void MCircularBuffer::pushFrontArr(char* items, std::size_t len)
{
	if (!this->canAddData(len)) // 存储空间必须要比实际数据至少多 1
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(len + this->mDynBuffer->mSize, this->mDynBuffer->mCapacity, this->mDynBuffer->mMaxCapacity);
		this->setCapacity(closeSize);
	}

	if (this->isLinearized())
	{
		if (len <= this->mFirst)
		{
			Array::Copy(items, 0, this->mDynBuffer->mBuffer, this->mFirst - len, len);
		}
		else
		{
			Array::Copy(items, len - this->mFirst, this->mDynBuffer->mBuffer, 0, this->mFirst);
			Array::Copy(items, 0, this->mDynBuffer->mBuffer, this->mDynBuffer->mCapacity - (len - this->mFirst), len - this->mFirst);
		}
	}
	else
	{
		Array::Copy(items, 0, this->mDynBuffer->mBuffer, this->mFirst - len, len);
	}

	if (len <= this->mFirst)
	{
		this->mFirst -= len;
	}
	else
	{
		this->mFirst = this->mDynBuffer->mCapacity - (len - this->mFirst);
	}

	this->mDynBuffer->mSize += len;
}

/**
* @brief 从 CB 中读取内容，并且将数据删除
*/
void MCircularBuffer::popFrontBA(MByteBuffer* bytearray, std::size_t len)
{
	this->frontBA(bytearray, len);
	this->popFrontLen(len);
}

// 仅仅是获取数据，并不删除
void MCircularBuffer::frontBA(MByteBuffer* bytearray, std::size_t len)
{
	bytearray->clear();          // 设置数据为初始值

	if (this->mDynBuffer->mSize >= len)          // 头部占据 4 个字节
	{
		if (this->isLinearized())      // 在一段连续的内存
		{
			bytearray->writeBytes(this->mDynBuffer->mBuffer, this->mFirst, len);
		}
		else if (this->mDynBuffer->mCapacity - this->mFirst >= len)
		{
			bytearray->writeBytes(this->mDynBuffer->mBuffer, this->mFirst, len);
		}
		else
		{
			bytearray->writeBytes(this->mDynBuffer->mBuffer, this->mFirst, this->mDynBuffer->mCapacity - this->mFirst);
			bytearray->writeBytes(this->mDynBuffer->mBuffer, 0, len - (this->mDynBuffer->mCapacity - this->mFirst));
		}
	}

	bytearray->setPos(0);        // 设置数据读取起始位置
}

/**
* @brief 从 CB 头部删除数据
*/
void MCircularBuffer::popFrontLen(uint32 len)
{
	if (this->isLinearized())  // 在一段连续的内存
	{
		this->mFirst += len;
	}
	else if (this->mDynBuffer->mCapacity - this->mFirst >= len)
	{
		this->mFirst += len;
	}
	else
	{
		this->mFirst = len - (this->mDynBuffer->mCapacity - this->mFirst);
	}

	this->mDynBuffer->mSize -= len;
}

// 向自己尾部添加一个 CirculeBuffer 
void MCircularBuffer::pushBackCB(MCircularBuffer* rhv)
{
	if (this->mDynBuffer->mCapacity - this->mDynBuffer->mSize < rhv->getSize())
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(rhv->getSize() + this->mDynBuffer->mSize, this->mDynBuffer->mCapacity, this->mDynBuffer->mMaxCapacity);
		this->setCapacity(closeSize);
	}
	//this.mSize += rhv.size;
	//this.mLast = this.mSize;

	//mTmpBA.clear();
	rhv->frontBA(mTmpBA, rhv->getSize());
	this->pushBackBA(mTmpBA);

	//if (rhv.isLinearized()) // 如果是在一段内存空间
	//{
	//    Array.Copy(rhv.buff, rhv.first, mBuffer, 0, rhv.size);
	//}
	//else    // 如果在两端内存空间
	//{
	//    Array.Copy(rhv.buff, rhv.first, mBuffer, 0, rhv.capacity() - rhv.first);
	//    Array.Copy(mBuffer, 0, mBuffer, rhv.capacity() - rhv.first, rhv.last);
	//}
	//rhv.clear();
}