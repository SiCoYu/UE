#include "MyProject.h"
#include "RefCountResLoadResultNotify.h"
#include "RefCount.h"

RefCountResLoadResultNotify::RefCountResLoadResultNotify()
{
	this->mRefCount = new RefCount();
}

RefCountResLoadResultNotify::~RefCountResLoadResultNotify()
{
	delete this->mRefCount;
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