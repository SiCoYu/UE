#ifndef __LockQueue_H
#define __LockQueue_H

#include <string>
#include "LockList.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

template <class T>
class LockQueue
{
protected:
	LockList<T> mList;

public:
	LockQueue(std::string name)
		: mList(name)
	{
		//mList = new LockList<T>("name");
	}

	void push(T item)
	{
		mList.Add(item);
	}

	T pop()
	{
		return mList.RemoveAt(0);
	}
};

MY_END_NAMESPACE

#endif