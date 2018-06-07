#ifndef __Singleton_H
#define __Singleton_H

template<class T>
class Singleton
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

	static void setSingletonPtr(T* value)
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