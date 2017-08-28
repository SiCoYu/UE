#include "MyProject.h"
#include "MCircularBuffer.h"
#include "DynBufResizePolicy.h"
#include "Array.h"
#include "ByteBuffer.h"

/**
 * @brief 构造函数
 */
MCircularBuffer::MCircularBuffer(size_t initCapacity, size_t maxCapacity)
{
	mDynBuffer = new DynBuffer<char>(initCapacity, maxCapacity);

	mFirst = 0;
	mLast = 0;

	mTmpBA = new ByteBuffer();
}

MCircularBuffer::~MCircularBuffer()
{
	delete mDynBuffer;
	delete mTmpBA;
}

uint32 MCircularBuffer::getFirst()
{
	return mFirst;
}

uint32 MCircularBuffer::getLast()
{
	return mLast;
}

char* MCircularBuffer::getBuffer()
{
	return mDynBuffer->mBuffer;
}

std::size_t MCircularBuffer::getSize()
{
	return mDynBuffer->mSize;
}

void MCircularBuffer::setSize(std::size_t value)
{
	mDynBuffer->setSize(value);
}

bool MCircularBuffer::isLinearized()
{
	if (this->getSize() == 0)
	{
		return true;
	}

	return mFirst < mLast;
}

bool MCircularBuffer::empty()
{
	return mDynBuffer->mSize == 0;
}

size_t MCircularBuffer::getCapacity()
{
	return mDynBuffer->mCapacity;
}

bool MCircularBuffer::full()
{
	return this->getCapacity() == this->getSize();
}

void MCircularBuffer::clear()
{
	mDynBuffer->mSize = 0;
	mFirst = 0;
	mLast = 0;
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
		char* tmp = new char[mLast];
		Array::Copy(mDynBuffer->mBuffer, 0, tmp, 0, mLast);  // 拷贝一段内存空间中的数据到 tmp
		Array::Copy(mDynBuffer->mBuffer, mFirst, mDynBuffer->mBuffer, 0, mDynBuffer->mCapacity - mFirst);  // 拷贝第一段数据到 0 索引位置
		Array::Copy(tmp, 0, mDynBuffer->mBuffer, mDynBuffer->mCapacity - mFirst, mLast);      // 拷贝第二段数据到缓冲区

		delete tmp;

		mFirst = 0;
		mLast = this->getSize();
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
		Array::Copy(mDynBuffer->mBuffer, mFirst, tmpbuff, 0, mDynBuffer->mSize);
	}
	else    // 如果在两端内存空间
	{
		Array::Copy(mDynBuffer->mBuffer, mFirst, tmpbuff, 0, mDynBuffer->mCapacity - mFirst);
		Array::Copy(mDynBuffer->mBuffer, 0, tmpbuff, mDynBuffer->mCapacity - mFirst, mLast);
	}

	mFirst = 0;
	mLast = mDynBuffer->mSize;
	mDynBuffer->mCapacity = newCapacity;
	delete mDynBuffer->mBuffer;
	mDynBuffer->mBuffer = tmpbuff;
}

/**
*@brief 能否添加 num 长度的数据
*/
bool MCircularBuffer::canAddData(uint32 num)
{
	if (mDynBuffer->mCapacity - mDynBuffer->mSize > num) // 浪费一个字节，不用 >= ，使用 > 
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
		uint32 closeSize = DynBufResizePolicy::getCloseSize(len + mDynBuffer->mSize, mDynBuffer->mCapacity, mDynBuffer->mMaxCapacity);
		setCapacity(closeSize);
	}

	if (isLinearized())
	{
		if (len <= (mDynBuffer->mCapacity - mLast))
		{
			Array::Copy(items, start, mDynBuffer->mBuffer, mLast, len);
		}
		else
		{
			Array::Copy(items, start, mDynBuffer->mBuffer, mLast, mDynBuffer->mCapacity - mLast);
			Array::Copy(items, mDynBuffer->mCapacity - mLast, mDynBuffer->mBuffer, 0, len - (mDynBuffer->mCapacity - mLast));
		}
	}
	else
	{
		Array::Copy(items, start, mDynBuffer->mBuffer, mLast, len);
	}

	mLast += len;
	mLast %= mDynBuffer->mCapacity;

	mDynBuffer->mSize += len;
}

void MCircularBuffer::pushBackBA(ByteBuffer* bu)
{
	//pushBack(bu.dynBuff.buff, bu.position, bu.bytesAvailable);
	pushBackArr(bu->getDynBuffer()->getBuffer(), 0, bu->getLength());
}

/**
*@brief 向存储空头部添加一段内容
*/
void MCircularBuffer::pushFrontArr(char* items, std::size_t len)
{
	if (!canAddData(len)) // 存储空间必须要比实际数据至少多 1
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(len + mDynBuffer->mSize, mDynBuffer->mCapacity, mDynBuffer->mMaxCapacity);
		setCapacity(closeSize);
	}

	if (isLinearized())
	{
		if (len <= mFirst)
		{
			Array::Copy(items, 0, mDynBuffer->mBuffer, mFirst - len, len);
		}
		else
		{
			Array::Copy(items, len - mFirst, mDynBuffer->mBuffer, 0, mFirst);
			Array::Copy(items, 0, mDynBuffer->mBuffer, mDynBuffer->mCapacity - (len - mFirst), len - mFirst);
		}
	}
	else
	{
		Array::Copy(items, 0, mDynBuffer->mBuffer, mFirst - len, len);
	}

	if (len <= mFirst)
	{
		mFirst -= len;
	}
	else
	{
		mFirst = mDynBuffer->mCapacity - (len - mFirst);
	}
	mDynBuffer->mSize += len;
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
	if (mDynBuffer->mSize >= len)          // 头部占据 4 个字节
	{
		if (isLinearized())      // 在一段连续的内存
		{
			bytearray->writeBytes(mDynBuffer->mBuffer, mFirst, len);
		}
		else if (mDynBuffer->mCapacity - mFirst >= len)
		{
			bytearray->writeBytes(mDynBuffer->mBuffer, mFirst, len);
		}
		else
		{
			bytearray->writeBytes(mDynBuffer->mBuffer, mFirst, mDynBuffer->mCapacity - mFirst);
			bytearray->writeBytes(mDynBuffer->mBuffer, 0, len - (mDynBuffer->mCapacity - mFirst));
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
		mFirst += len;
	}
	else if (mDynBuffer->mCapacity - mFirst >= len)
	{
		mFirst += len;
	}
	else
	{
		mFirst = len - (mDynBuffer->mCapacity - mFirst);
	}

	mDynBuffer->mSize -= len;
}

// 向自己尾部添加一个 CirculeBuffer 
void MCircularBuffer::pushBackCB(MCircularBuffer* rhv)
{
	if (mDynBuffer->mCapacity - mDynBuffer->mSize < rhv->getSize())
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(rhv->getSize() + mDynBuffer->mSize, mDynBuffer->mCapacity, mDynBuffer->mMaxCapacity);
		setCapacity(closeSize);
	}
	//this.mSize += rhv.size;
	//this.mLast = this.mSize;

	//mTmpBA.clear();
	rhv->frontBA(mTmpBA, rhv->getSize());
	pushBackBA(mTmpBA);

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