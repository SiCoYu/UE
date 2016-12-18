#include "MyProject.h"
#include "ResItem.h"
#include "RefCountResLoadResultNotify.h"
#include "ResLoadState.h"
#include "ResEventDispatch.h"
#include "RefCount.h"

ResItem::ResItem()
{
	mRefCountResLoadResultNotify = new RefCountResLoadResultNotify();
}

ResPackType ResItem::getResPackType()
{
	return mResPackType;
}

void ResItem::setResPackType(ResPackType value)
{
	mResPackType = value;
}

std::string ResItem::getPath()
{
	return mPath;
}

void ResItem::setPath(std::string value)
{
	mPath = value;
}

std::string ResItem::getPathNoExt()
{
	return mPathNoExt;
}

void ResItem::setPathNoExt(std::string value)
{
	mPathNoExt = value;
}

std::string ResItem::getExtName()
{
	return mExtName;
}

void ResItem::setExtName(std::string value)
{
	mExtName = value;
}

bool ResItem::getResNeedCoroutine()
{
	return mIsResNeedCoroutine;
}

void ResItem::setResNeedCoroutine(bool value)
{
	mIsResNeedCoroutine = value;
}

ResLoadType ResItem::getResLoadType()
{
	return mResLoadType;
}

void ResItem::setResLoadType(ResLoadType value)
{
	mResLoadType = value;
}

RefCountResLoadResultNotify* ResItem::getRefCountResLoadResultNotify()
{
	return mRefCountResLoadResultNotify;
}

void ResItem::setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value)
{
	mRefCountResLoadResultNotify = value;
}

std::string ResItem::getPrefabName()         // 只有 Prefab 资源才实现这个函数
{
	return "";
}

void ResItem::init(LoadItem* item)
{
	mRefCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
}

void ResItem::failed(LoadItem* item)
{
	mRefCountResLoadResultNotify->getResLoadState()->setFailed();
	mRefCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

void ResItem::reset()
{
	mPath = "";
	mRefCountResLoadResultNotify->getResLoadState()->reset();
	mRefCountResLoadResultNotify->getRefCount()->setRefNum(0);
}

// 卸载
void ResItem::unload()
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
	mResPackType = rhv->mResPackType;
	mResLoadType = rhv->mResLoadType;
	mPath = rhv->mPath;
	mPathNoExt = rhv->mPathNoExt;
	mExtName = rhv->mExtName;
	mIsResNeedCoroutine = rhv->mIsResNeedCoroutine;
	mRefCountResLoadResultNotify->copyFrom(rhv->getRefCountResLoadResultNotify());
}