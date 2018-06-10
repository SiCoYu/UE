#ifndef __MDynBuffer_H
#define __MDynBuffer_H

#include "Platform.h"
#include <cstddef>
#include "BufferCV.h"
#include "DynBufResizePolicy.h"
#include "GObject.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 动态增长缓冲区，不分类型，就是 byte 缓冲区
 */
template <class T>
class MDynBuffer : public GObject
{
	friend class MClientBuffer;

public:
	std::size_t mCapacity;
	std::size_t mMaxCapacity;
	std::size_t mSize;
	T* mBuffer;
	bool mIsPodType;

public:
	MDynBuffer(
		size_t initCapacity = (size_t)BufferCV::eINIT_CAPACITY,
		size_t maxCapacity = (size_t)BufferCV::eMAX_CAPACITY
	)
		: mCapacity(initCapacity), 
		  mMaxCapacity(maxCapacity)
	{
		this->mSize = 0;
		this->mBuffer = MY_NEW T[this->mCapacity];
		this->mIsPodType = false;
	}

	~MDynBuffer()
	{
		//this->dispose();
	}

	void dispose()
	{
		if (this->mIsPodType)
		{
			MY_DELETE_BASE_TYPE_ARRAY(this->mBuffer, T, this->mCapacity);
		}
		else
		{
			MY_DELETE[] this->mBuffer;
		}
	}

	void setPodType(bool value)
	{
		this->mIsPodType = value;
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
		return this->mSize;
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
		this->setCapacity(
			DynBufResizePolicy::getCloseSize(
				this->getSize() + delta, 
				this->getCapacity(), 
				this->getMaxCapacity()
			)
		);
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
		bool ret = false;

		if (this->mCapacity - this->mSize >= num)
		{
			ret = true;
		}

		return ret;
	}
};

MY_END_NAMESPACE

#endif			// __MDynBuffer_H