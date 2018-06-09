#ifndef __Singleton_H
#define __Singleton_H

#include "GObject.h"

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
			T::msSingleton = new T();
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
			delete T::msSingleton;
			T::msSingleton = nullptr;
		}
	}
};

#endif				// __Singleton_H