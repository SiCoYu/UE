#include "MyLazyObjectPtr.h"
#include "UtilStr.h"

MY_BEGIN_NAMESPACE(MyNS)

template<class T>
MyLazyObjectPtr::MyLazyObjectPtr()
{

}

template<class T>
MyLazyObjectPtr::~MyLazyObjectPtr()
{

}

template<class T>
UObject* MyLazyObjectPtr::getObject() const
{
	// UObject/PersistentObjectPtr.h
	// FORCEINLINE UObject* Get() const
	return this->mNativeLazyObjectPtr.Get();
}

MY_END_NAMESPACE