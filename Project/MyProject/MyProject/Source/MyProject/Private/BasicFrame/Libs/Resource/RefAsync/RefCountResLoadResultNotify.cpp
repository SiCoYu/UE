#include "MyProject.h"
#include "RefCountResLoadResultNotify.h"
#include "RefCount.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

RefCountResLoadResultNotify::RefCountResLoadResultNotify()
{
	this->mRefCount = MY_NEW RefCount();
}

RefCountResLoadResultNotify::~RefCountResLoadResultNotify()
{
	//this->dispose();
}

void RefCountResLoadResultNotify::init()
{

}

void RefCountResLoadResultNotify::dispose()
{
	MY_SAFE_DISPOSE(this->mRefCount);
}

RefCount* RefCountResLoadResultNotify::getRefCount()
{
	return this->mRefCount;
}

void RefCountResLoadResultNotify::setRefCount(RefCount* value)
{
	this->mRefCount = value;
}

void RefCountResLoadResultNotify::copyFrom(ResLoadResultNotify* rhv)
{
	ResLoadResultNotify::copyFrom(rhv);
	this->mRefCount->copyFrom(((RefCountResLoadResultNotify*)(rhv))->getRefCount());
}

MY_END_NAMESPACE