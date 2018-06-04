#include "MyProject.h"
#include "PriorityProcessObject.h"

MY_BEGIN_NAMESPACE(MyNS)

PriorityProcessObject::PriorityProcessObject()
{
	this->onPutInPool();
}

void PriorityProcessObject::putInPool()
{
	this->onPutInPool();
}

void PriorityProcessObject::getFromPool()
{
	this->onGetFromPool();
}

void PriorityProcessObject::dispose()
{
	this->onPutInPool();
}

void PriorityProcessObject::setIsUsePool(bool value)
{
	//this->mIsUsePool = value;
}

bool PriorityProcessObject::isUsePool()
{
	//return this->mIsUsePool;
	return false;
}

void PriorityProcessObject::onPutInPool()
{
	this->mPriorityObject = nullptr;
	this->mPriority = 0.0f;
}

void PriorityProcessObject::onGetFromPool()
{

}

int PriorityProcessObject::getBufferType()
{
	return 0;
}

MY_END_NAMESPACE