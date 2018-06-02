#ifndef __MLockQueue_H
#define __MLockQueue_H

#include <string>
#include "MLockList.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

template <class T>
class MLockQueue
{
protected:
	MLockList<T> mList;

public:
	MLockQueue(std::string name)
		: mList(name)
	{
		//mList = new MLockList<T>("name");
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