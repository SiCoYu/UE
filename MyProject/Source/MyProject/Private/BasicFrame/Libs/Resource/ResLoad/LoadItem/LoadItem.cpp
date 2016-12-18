#include "MyProject.h"
#include "LoadItem.h"
#include "NonRefCountResLoadResultNotify.h"
#include "ResLoadState.h"

LoadItem::LoadItem()
{
	mNonRefCountResLoadResultNotify = new NonRefCountResLoadResultNotify();
}

ResPackType LoadItem::getResPackType()
{
	return mResPackType;
}

void LoadItem::setResPackType(ResPackType value)
{
	mResPackType = value;
}

std::string LoadItem::getPath()
{
	return mPath;
}

void LoadItem::setPath(std::string value)
{
	mPath = value;
}

std::string LoadItem::getPathNoExt()
{
	return mPathNoExt;
}

void LoadItem::setPathNoExt(std::string value)
{
	mPathNoExt = value;
}

std::string LoadItem::getExtName()
{
	return mExtName;
}

void LoadItem::setExtName(std::string value)
{
	mExtName = value;
}

bool LoadItem::getLoadNeedCoroutine()
{
	return mIsLoadNeedCoroutine;
}

void LoadItem::setLoadNeedCoroutine(bool value)
{
	mIsLoadNeedCoroutine = value;
}

ResLoadType LoadItem::getResLoadType()
{
	return mResLoadType;
}

void LoadItem::setResLoadType(ResLoadType value)
{
	mResLoadType = value;
}

NonRefCountResLoadResultNotify* LoadItem::getNonRefCountResLoadResultNotify()
{
	return mNonRefCountResLoadResultNotify;
}

void LoadItem::setNonRefCountResLoadResultNotify(NonRefCountResLoadResultNotify* value)
{
	mNonRefCountResLoadResultNotify = value;
}

void LoadItem::load()
{
	mNonRefCountResLoadResultNotify->getResLoadState()->setLoading();
}

// 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
void LoadItem::unload()
{

}

void LoadItem::reset()
{
	mPath = "";
	mIsLoadNeedCoroutine = false;
}