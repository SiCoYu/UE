#ifndef __LockList_H
#define __LockList_H

#include "DynBuffer.h"
#include "MMutex.h"
#include "Platform.h"
#include <string>

/**
 * @brief 线程安全列表， T 是 Object ，便于使用 Equal 比较地址
 */
template <class T>
class LockList
{
protected:
	DynBuffer<T> mDynamicBuffer;
    MMutex* mVisitMutex;
    T mRetItem;

public:
	LockList(std::string name, uint32 initCapacity = 32/*BufferCV.INIT_ELEM_CAPACITY*/, uint32 maxCapacity = 8 * 1024 * 1024/*BufferCV.MAX_CAPACITY*/)
		: mDynamicBuffer(initCapacity, maxCapacity)
	{
		//mDynamicBuffer = new DynBuffer<T>(initCapacity, maxCapacity);
		mVisitMutex = new MMutex();
	}

	~LockList()
	{
		delete mVisitMutex;
	}

	uint32 getCount()
	{
		MLock mlock(mVisitMutex);
		{
			return mDynamicBuffer.mSize;
		}
	}

	T& operator[](int index)
	{
		MLock mlock(mVisitMutex);
		{
			if (index < mDynamicBuffer.mSize)
			{
				return mDynamicBuffer.mBuffer[index];
			}
			else
			{
				return mRetItem;
			}
		}
	}

	void Add(T item)
	{
		MLock mlock(mVisitMutex);
		{
			if (mDynamicBuffer.mSize >= mDynamicBuffer.mCapacity)
			{
				mDynamicBuffer.extendDeltaCapicity(1);
			}

			mDynamicBuffer.mBuffer[mDynamicBuffer.mSize] = item;
			++mDynamicBuffer.mSize;
		}
	}

	bool Remove(T item)
	{
		MLock mlock(mVisitMutex);
		{
			int idx = 0;
			foreach(var elem in mDynamicBuffer.mBuffer)
			{
				if (item.Equals(elem))       // 地址比较
				{
					this.RemoveAt(idx);
					return true;
				}

				++idx;
			}
			return false;
		}
	}

	T RemoveAt(int index)
	{
		MLock mlock(mVisitMutex);
		{
			if (index < mDynamicBuffer.mSize)
			{
				mRetItem = mDynamicBuffer.mBuffer[index];

				if (index < mDynamicBuffer.mSize)
				{
					if (index != mDynamicBuffer.mSize - 1 && 1 != mDynamicBuffer.mSize) // 如果删除不是最后一个元素或者总共就大于一个元素
					{
						Array.Copy(mDynamicBuffer.mBuffer, index + 1, mDynamicBuffer.mBuffer, index, mDynamicBuffer.mSize - 1 - index);
					}

					--mDynamicBuffer.mSize;
				}
			}
			else
			{
				mRetItem = default(T);
			}

			return mRetItem;
		}
	}

	int IndexOf(T item)
	{
		MLock mlock(mVisitMutex);
		{
			int idx = 0;
			foreach(var elem in mDynamicBuffer.mBuffer)
			{
				if (item.Equals(elem))       // 地址比较
				{
					this.RemoveAt(idx);
					return idx;
				}

				++idx;
			}
			return -1;
		}
	}
};

#endif