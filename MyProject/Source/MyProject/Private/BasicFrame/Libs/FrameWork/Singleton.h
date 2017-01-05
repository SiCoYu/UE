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
		if (nullptr == msSingleton)
		{
			msSingleton = new T();
		}

		return msSingleton;
	}

	static void deleteSingletonPtr()
	{
		if (nullptr != msSingleton)
		{
			delete msSingleton;
			msSingleton = nullptr;
		}
	}
};

#endif				// __Singleton_H