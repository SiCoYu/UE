#ifndef __Singleton_H
#define __Singleton_H

#include "GObject.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

template<class T>
class Singleton : public GObject
{
private:
	static T* msSingleton;

public:
	static T* getSingletonPtr()
	{
		if (nullptr == T::msSingleton)
		{
			T::msSingleton = MY_NEW T();
		}

		return T::msSingleton;
	}

	static T* setSingletonPtr(T* value)
	{
		if (nullptr == T::msSingleton)
		{
			T::msSingleton = value;
		}

		return T::msSingleton;
	}

	static void deleteSingletonPtr()
	{
		if (nullptr != T::msSingleton)
		{
			MY_DELETE T::msSingleton;
			T::msSingleton = nullptr;
		}
	}
};

MY_END_NAMESPACE

#endif				// __Singleton_H