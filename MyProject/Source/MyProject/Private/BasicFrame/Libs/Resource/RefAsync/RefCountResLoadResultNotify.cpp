#include "MyProject.h"
#include "RefCountResLoadResultNotify.h"
#include "RefCount.h"

RefCountResLoadResultNotify::RefCountResLoadResultNotify()
{
	mRefCount = new RefCount();
}

RefCountResLoadResultNotify::~RefCountResLoadResultNotify()
{
	delete mRefCount;
}

RefCount* RefCountResLoadResultNotify::getRefCount()
{
	return mRefCount;
}

void RefCountResLoadResultNotify::setRefCount(RefCount* value)
{
	mRefCount = value;
}

void RefCountResLoadResultNotify::copyFrom(ResLoadResultNotify* rhv)
{
	ResLoadResultNotify::copyFrom(rhv);
	mRefCount->copyFrom(((RefCountResLoadResultNotify*)(rhv))->getRefCount());
}