#include "MyProject.h"
#include "GPoolObject.h"
#include "TypeDef.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(GPoolObject, MyAllocatedObject)

GPoolObject::GPoolObject()
{
	this->mIsUsePool = false;
	this->onGetFromPool();
}

void GPoolObject::init()
{
	this->onInit();
}

void GPoolObject::onInit()
{

}

void GPoolObject::onGetFromPool()
{

}

void GPoolObject::onPutInPool()
{

}

void GPoolObject::dispose()
{
	this->onPutInPool();
	this->onDestroy();
}

void GPoolObject::destroy()
{
	this->onDestroy();
}

void GPoolObject::onDestroy()
{

}

bool GPoolObject::isUsePool()
{
	return this->mIsUsePool;
}

void GPoolObject::setIsUsePool(bool value)
{
	this->mIsUsePool = value;
}

void GPoolObject::putInPool()
{
	this->onPutInPool();
}

void GPoolObject::getFromPool()
{
	this->onGetFromPool();
}

void GPoolObject::setGlobalUniqueId(std::string value)
{
	this->mGlobalUniqueId = value;
}

std::string GPoolObject::getGlobalUniqueId()
{
	return this->mGlobalUniqueId;
}

void GPoolObject::resetDefault()
{

}

MY_END_NAMESPACE