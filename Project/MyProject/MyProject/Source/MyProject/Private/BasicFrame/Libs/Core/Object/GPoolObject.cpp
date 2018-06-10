#include "MyProject.h"
#include "GPoolObject.h"
#include "TypeDef.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(GPoolObject, GObjectBase)

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

void GPoolObject::setNumUniqueId(int value)
{
	this->mNumUniqueId = value;
}

int GPoolObject::getNumUniqueId()
{
	return this->mNumUniqueId;
}

void GPoolObject::setStrUniqueId(std::string value)
{
	this->mStrUniqueId = value;
}

std::string GPoolObject::getStrUniqueId()
{
	return this->mStrUniqueId;
}

MY_END_NAMESPACE