#ifndef __MLockList_H
#define __MLockList_H

#include "MDynBuffer.h"
#include "MMutex.h"
#include "Platform.h"
#include <string>
#include "MLock.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 线程安全列表， T 是 Object ，便于使用 Equal 比较地址
 */
template <class T>
class MLockList
{
protected:
	MDynBuffer<T> mDynamicBuffer;
    MMutex* mVisitMutex;
    T mRetItem;

public:
	MLockList(
		std::string name, 
		uint32 initCapacity = 32/*BufferCV.eINIT_ELEM_CAPACITY*/, 
		uint32 maxCapacity = 8 * 1024 * 1024/*BufferCV.eMAX_CAPACITY*/
	)
		: mDynamicBuffer(initCapacity, maxCapacity)
	{
		//mDynamicBuffer = new MDynBuffer<T>(initCapacity, maxCapacity);
		this->mVisitMutex = MY_NEW MMutex();
	}

	~MLockList()
	{
		MY_DELETE this->mVisitMutex;
	}

	uint32 getCount()
	{
		MLock mlock(this->mVisitMutex);
		{
			return this->mDynamicBuffer.mSize;
		}
	}

	T& operator[](int index)
	{
		MLock mlock(this->mVisitMutex);
		{
			if (index < this->mDynamicBuffer.mSize)
			{
				return this->mDynamicBuffer.mBuffer[index];
			}
			else
			{
				return this->mRetItem;
			}
		}
	}

	void Add(T item)
	{
		MLock mlock(mVisitMutex);
		{
			if (this->mDynamicBuffer.mSize >= this->mDynamicBuffer.mCapacity)
			{
				this->mDynamicBuffer.extendDeltaCapicity(1);
			}

			this->mDynamicBuffer.mBuffer[mDynamicBuffer.mSize] = item;
			++this->mDynamicBuffer.mSize;
		}
	}

	bool Remove(T item)
	{
		MLock mlock(this->mVisitMutex);
		{
			int idx = 0;
			foreach(var elem in this->mDynamicBuffer.mBuffer)
			{
				if (item.Equals(elem))       // 地址比较
				{
					this->RemoveAt(idx);
					return true;
				}

				++idx;
			}
			return false;
		}
	}

	T RemoveAt(int index)
	{
		MLock mlock(this->mVisitMutex);
		{
			if (index < this->mDynamicBuffer.mSize)
			{
				this->mRetItem = this->mDynamicBuffer.mBuffer[index];

				if (index < this->mDynamicBuffer.mSize)
				{
					if (index != this->mDynamicBuffer.mSize - 1 && 1 != this->mDynamicBuffer.mSize) // 如果删除不是最后一个元素或者总共就大于一个元素
					{
						Array::Copy(this->mDynamicBuffer.mBuffer, index + 1, this->mDynamicBuffer.mBuffer, index, this->mDynamicBuffer.mSize - 1 - index);
					}

					--this->mDynamicBuffer.mSize;
				}
			}
			else
			{
				this->mRetItem = nullptr;
			}

			return this->mRetItem;
		}
	}

	int IndexOf(T item)
	{
		MLock mlock(this->mVisitMutex);
		{
			int idx = 0;

			foreach(var elem in this->mDynamicBuffer.mBuffer)
			{
				if (item.Equals(elem))       // 地址比较
				{
					this->RemoveAt(idx);
					return idx;
				}

				++idx;
			}

			return -1;
		}
	}
};

MY_END_NAMESPACE

#endif