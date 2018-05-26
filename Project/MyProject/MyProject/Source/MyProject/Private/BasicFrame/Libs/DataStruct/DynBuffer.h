#ifndef __DynBuffer_H
#define __DynBuffer_H

#include "Platform.h"
#include <cstddef>
#include "BufferCV.h"
#include "DynBufResizePolicy.h"
#include "GObject.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"

/**
 * @brief 动态增长缓冲区，不分类型，就是 byte 缓冲区
 */
template <class T>
class DynBuffer : public GObject
{
	friend class ClientBuffer;

public:
	std::size_t mCapacity;
	std::size_t mMaxCapacity;
	std::size_t mSize;
	T* mBuffer;

public:
	DynBuffer(
		size_t initCapacity = BufferCV::INIT_CAPACITY, 
		size_t maxCapacity = BufferCV::MAX_CAPACITY
	)
		: mCapacity(initCapacity), 
		  mMaxCapacity(maxCapacity)
	{
		this->mSize = 0;
		this->mBuffer = MY_NEW T[mCapacity];
	}

	~DynBuffer()
	{
		delete[] this->mBuffer;
	}

	T* getBuffer()
	{
		return this->mBuffer;
	}

	void setBuffer(char* value, uint32 len)
	{
		this->mBuffer = value;
		this->mCapacity = len;
	}

	std::size_t getMaxCapacity()
	{
		return this->mMaxCapacity;
	}

	std::size_t getCapacity()
	{
		return this->mCapacity;
	}

	void setCapacity(std::size_t value)
	{
		if (value == this->mCapacity)
		{
			return;
		}
		if (value < this->getSize())       // 不能分配比当前已经占有的空间还小的空间
		{
			return;
		}

		T* tmpbuff = MY_NEW T[value];   // 分配新的空间
		memcpy(tmpbuff, this->mBuffer, this->mCapacity);

		delete[] this->mBuffer;
		this->mBuffer = tmpbuff;
		this->mCapacity = value;
	}

	std::size_t getSize()
	{
		return mSize;
	}

	void setSize(std::size_t value)
	{
		if (this->mSize > this->getCapacity())
		{
			this->extendDeltaCapicity(value - this->getSize());
		}

		this->mSize = value;
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
		if (this->mCapacity - this->mSize >= num)
		{
			return true;
		}

		return false;
	}
};

#endif			// __DYNBUFFER_H