#include "MyProject.h"
#include "LoadItem.h"
#include "NonRefCountResLoadResultNotify.h"
#include "ResLoadState.h"
#include "LoadParam.h"

#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

LoadItem::LoadItem()
{
	this->mNonRefCountResLoadResultNotify = MY_NEW NonRefCountResLoadResultNotify();
}

LoadItem::~LoadItem()
{
	
}

ResPackType LoadItem::getResPackType()
{
	return this->mResPackType;
}

void LoadItem::setResPackType(ResPackType value)
{
	mResPackType = value;
}

std::string LoadItem::getPath()
{
	return this->mPath;
}

void LoadItem::setPath(std::string value)
{
	this->mPath = value;
}

std::string LoadItem::getPathNoExt()
{
	return mPathNoExt;
}

void LoadItem::setPathNoExt(std::string value)
{
	this->mPathNoExt = value;
}

std::string LoadItem::getExtName()
{
	return this->mExtName;
}

void LoadItem::setExtName(std::string value)
{
	mExtName = value;
}

bool LoadItem::getLoadNeedCoroutine()
{
	return this->mIsLoadNeedCoroutine;
}

void LoadItem::setLoadNeedCoroutine(bool value)
{
	this->mIsLoadNeedCoroutine = value;
}

ResLoadType LoadItem::getResLoadType()
{
	return this->mResLoadType;
}

void LoadItem::setResLoadType(ResLoadType value)
{
	this->mResLoadType = value;
}

NonRefCountResLoadResultNotify* LoadItem::getNonRefCountResLoadResultNotify()
{
	return this->mNonRefCountResLoadResultNotify;
}

void LoadItem::setNonRefCountResLoadResultNotify(NonRefCountResLoadResultNotify* value)
{
	this->mNonRefCountResLoadResultNotify = value;
}

UObject* LoadItem::getObject()
{
	return nullptr;
}

void LoadItem::setObject(UObject* value)
{

}

void LoadItem::load()
{
	this->mNonRefCountResLoadResultNotify->getResLoadState()->setLoading();
}

// 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
void LoadItem::unload()
{

}

void LoadItem::reset()
{
	this->mPath = "";
	this->mIsLoadNeedCoroutine = false;
}

void LoadItem::setLoadParam(LoadParam* param)
{
	this->setResPackType(param->getResPackType());
	this->setResLoadType(param->getResLoadType());
	this->setPath(param->getPath());
	this->setPathNoExt(param->getPathNoExt());
	this->setExtName(param->getExtName());
	this->setLoadNeedCoroutine(param->getIsLoadNeedCoroutine());
}

MY_END_NAMESPACE