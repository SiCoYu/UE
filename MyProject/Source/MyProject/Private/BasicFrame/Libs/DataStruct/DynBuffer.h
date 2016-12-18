#ifndef __DYNBUFFER_H
#define __DYNBUFFER_H

#include "Platform.h"
#include <cstddef>
#include "BufferCV.h"
#include "DynBufResizePolicy.h"

/**
 * @brief 动态增长缓冲区，不分类型，就是 byte 缓冲区
 */
template <class T>
class DynBuffer
{
	friend class ClientBuffer;

public:
	std::size_t mCapacity;
	std::size_t mMaxCapacity;
	std::size_t mSize;
	T* mBuffer;

public:
	DynBuffer(size_t initCapacity = BufferCV::INIT_CAPACITY, size_t maxCapacity = BufferCV::MAX_CAPACITY)
		: mCapacity(initCapacity), mMaxCapacity(maxCapacity)
	{
		mSize = 0;
		mBuffer = new T[mCapacity];
	}

	~DynBuffer()
	{
		delete[] mBuffer;
	}

	T* getBuffer()
	{
		return mBuffer;
	}

	void setBuff(char* value, uint32 len)
	{
		mBuffer = value;
		mCapacity = len;
	}

	std::size_t getMaxCapacity()
	{
		return mMaxCapacity;
	}

	std::size_t getCapacity()
	{
		return mCapacity;
	}

	void setCapacity(std::size_t value)
	{
		if (value == mCapacity)
		{
			return;
		}
		if (value < this->getSize())       // 不能分配比当前已经占有的空间还小的空间
		{
			return;
		}

		char* tmpbuff = new char[value];   // 分配新的空间
		memcpy(tmpbuff, mBuffer, mCapacity);

		delete[] mBuffer;
		mBuffer = tmpbuff;
		mCapacity = value;
	}

	std::size_t getSize()
	{
		return mSize;
	}

	void setSize(std::size_t value)
	{
		if (mSize > this->getCapacity())
		{
			extendDeltaCapicity(value - this->getSize());
		}

		mSize = value;
	}

	void extendDeltaCapicity(uint32 delta)
	{
		this->setCapacity(DynBufResizePolicy::getCloseSize(this->getSize() + delta, this->getCapacity(), this->getMaxCapacity()));
	}

	//void push(char* pItem, std::size_t len)
	//{
	//	if (len > mCapacity)
	//	{
	//		uint32 closeSize = DynBufResizePolicy::getCloseSize(len, this->getCapacity(), this->getMaxCapacity());
	//		setCapacity(closeSize);
	//	}
	//
	//	memcpy(mBuffer, pItem, len);
	//	mSize = len;
	//}

	bool canAddData(uint32 num)
	{
		if (mCapacity - mSize >= num)
		{
			return true;
		}

		return false;
	}
};

#endif			// __DYNBUFFER_H