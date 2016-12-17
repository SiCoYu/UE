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
		if (msSingleton == NULL)
		{
			msSingleton = new T();
		}

		return msSingleton;
	}
};

#endif				// __Singleton_H