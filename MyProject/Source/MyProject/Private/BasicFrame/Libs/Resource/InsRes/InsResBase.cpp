#include "MyProject.h"
#include "InsResBase.h"
#include "RefCountResLoadResultNotify.h"
#include "ResLoadState.h"

InsResBase::InsResBase()
{
#if PKG_RES_LOAD
	this->mIsOrigResNeedImmeUnload = false;
#else
	this->mIsOrigResNeedImmeUnload = true;
#endif
	this->mRefCountResLoadResultNotify = new RefCountResLoadResultNotify();
}

bool InsResBase::getIsOrigResNeedImmeUnload()
{
	return this->mIsOrigResNeedImmeUnload;
}

void InsResBase::setIsOrigResNeedImmeUnload(bool value)
{
	this->mIsOrigResNeedImmeUnload = value;
}

std::string InsResBase::GetPath()
{
	return this->mPath;
}

std::string InsResBase::getPrefabName()         // 只有 Prefab 资源才实现这个函数
{
	return "";
}

void InsResBase::init(ResItem* res)
{
	this->initImpl(res);         // 内部初始化完成后，才分发事件
	this->mRefCountResLoadResultNotify->onLoadEventHandle(this);
}

// 这个是内部初始化实现，初始化都重载这个，但是现在很多都是重在了
void InsResBase::initImpl(ResItem* res)
{

}

void InsResBase::failed(ResItem* res)
{
	this->unload();
	this->mRefCountResLoadResultNotify->onLoadEventHandle(this);
}

void InsResBase::unload()
{

}

RefCountResLoadResultNotify* InsResBase::getRefCountResLoadResultNotify()
{
	return this->mRefCountResLoadResultNotify;
}

void InsResBase::setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value)
{
	this->mRefCountResLoadResultNotify = value;
}

std::string InsResBase::getLogicPath()
{
	return "";
}

bool InsResBase::hasSuccessLoaded()
{
	return this->mRefCountResLoadResultNotify->getResLoadState()->hasSuccessLoaded();
}

bool InsResBase::hasFailed()
{
	return this->mRefCountResLoadResultNotify->getResLoadState()->hasFailed();
}

std::string InsResBase::getResUniqueId()
{
	return "";
}