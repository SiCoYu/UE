#include "MyProject.h"
#include "ResItem.h"
#include "RefCountResLoadResultNotify.h"
#include "ResLoadState.h"
#include "ResEventDispatch.h"
#include "RefCount.h"
#include "LoadParam.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ResItem, GObject)

ResItem::ResItem()
{
	this->mRefCountResLoadResultNotify = MY_NEW RefCountResLoadResultNotify();
}

ResItem::~ResItem()
{
	
}

ResPackType ResItem::getResPackType()
{
	return this->mResPackType;
}

void ResItem::setResPackType(ResPackType value)
{
	this->mResPackType = value;
}

std::string ResItem::getPath()
{
	return this->mPath;
}

void ResItem::setPath(std::string value)
{
	this->mPath = value;
}

std::string ResItem::getPathNoExt()
{
	return this->mPathNoExt;
}

void ResItem::setPathNoExt(std::string value)
{
	this->mPathNoExt = value;
}

std::string ResItem::getExtName()
{
	return this->mExtName;
}

void ResItem::setExtName(std::string value)
{
	this->mExtName = value;
}

bool ResItem::getResNeedCoroutine()
{
	return this->mIsResNeedCoroutine;
}

void ResItem::setResNeedCoroutine(bool value)
{
	this->mIsResNeedCoroutine = value;
}

ResLoadType ResItem::getResLoadType()
{
	return this->mResLoadType;
}

void ResItem::setResLoadType(ResLoadType value)
{
	this->mResLoadType = value;
}

RefCountResLoadResultNotify* ResItem::getRefCountResLoadResultNotify()
{
	return this->mRefCountResLoadResultNotify;
}

void ResItem::setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value)
{
	this->mRefCountResLoadResultNotify = value;
}

std::string ResItem::getPrefabName()         // 只有 Prefab 资源才实现这个函数
{
	return "";
}

void ResItem::initWithLoad(LoadItem* item)
{
	this->init();

	this->mRefCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
}

void ResItem::failed(LoadItem* item)
{
	this->mRefCountResLoadResultNotify->getResLoadState()->setFailed();
	this->mRefCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

void ResItem::reset()
{
	this->mPath = "";
	this->mRefCountResLoadResultNotify->getResLoadState()->reset();
	this->mRefCountResLoadResultNotify->getRefCount()->setRefNum(0);
}

// 卸载
void ResItem::unload()
{

}

void ResItem::init()
{
	Super::init();
}

void ResItem::dispose()
{

}

UObject* ResItem::InstantiateObject(std::string resName)
{
	return nullptr;
}

UObject* ResItem::getObject(std::string resName)
{
	return nullptr;
}

uint8* ResItem::getBytes(std::string resName)            // 获取字节数据
{
	return nullptr;
}

std::string ResItem::getText(std::string resName)
{
	return "";
}

void ResItem::copyFrom(ResItem* rhv)
{
	this->mResPackType = rhv->mResPackType;
	this->mResLoadType = rhv->mResLoadType;
	this->mPath = rhv->mPath;
	this->mPathNoExt = rhv->mPathNoExt;
	this->mExtName = rhv->mExtName;
	this->mIsResNeedCoroutine = rhv->mIsResNeedCoroutine;
	this->mRefCountResLoadResultNotify->copyFrom(rhv->getRefCountResLoadResultNotify());
}

bool ResItem::hasSuccessLoaded()
{
	return this->mRefCountResLoadResultNotify->getResLoadState()->hasSuccessLoaded();
}

bool ResItem::hasFailed()
{
	return this->mRefCountResLoadResultNotify->getResLoadState()->hasFailed();
}

std::string ResItem::getResUniqueId()
{
	return "";
}

void ResItem::setLoadParam(LoadParam* param)
{
	this->setResNeedCoroutine(param->getIsResNeedCoroutine());
	this->setResPackType(param->getResPackType());
	this->setResLoadType(param->getResLoadType());
	this->setPath(param->getPath());
	this->setPathNoExt(param->getPathNoExt());
	this->setExtName(param->getExtName());
}

MY_END_NAMESPACE