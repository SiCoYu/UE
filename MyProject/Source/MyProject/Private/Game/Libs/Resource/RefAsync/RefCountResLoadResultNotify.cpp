#include "MyProject.h"
#include "RefCountResLoadResultNotify.h"
#include "RefCount.h"

RefCountResLoadResultNotify::RefCountResLoadResultNotify()
{
	m_refCount = new RefCount();
}

RefCountResLoadResultNotify::~RefCountResLoadResultNotify()
{
	delete m_refCount;
}

RefCount* RefCountResLoadResultNotify::getRefCount()
{
	return m_refCount;
}

void RefCountResLoadResultNotify::setRefCount(RefCount* value)
{
	m_refCount = value;
}

void RefCountResLoadResultNotify::copyFrom(ResLoadResultNotify* rhv)
{
	ResLoadResultNotify::copyFrom(rhv);
	m_refCount->copyFrom(((RefCountResLoadResultNotify*)(rhv))->getRefCount());
}