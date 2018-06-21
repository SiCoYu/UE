#include "MyProject.h"
#include "MyLazyObjectPtr.h"
#include "UtilStr.h"

MyLazyObjectPtr::MyLazyObjectPtr()
{

}

MyLazyObjectPtr::~MyLazyObjectPtr()
{

}

UObject* MyLazyObjectPtr::getObject() const
{
	// UObject/PersistentObjectPtr.h
	// FORCEINLINE UObject* Get() const
	return this->mNativeLazyObjectPtr.Get();
}