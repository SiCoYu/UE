#include "MyProject.h"
#include "ResInsBase.h"
#include "RefCountResLoadResultNotify.h"
#include "ResLoadState.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MClassFactory.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ResInsBase, GObject)

ResInsBase::ResInsBase()
{
#ifdef PKG_RES_LOAD
	this->mIsOrigResNeedImmeUnload = false;
#else
	this->mIsOrigResNeedImmeUnload = true;
#endif
	this->mRefCountResLoadResultNotify = MY_NEW RefCountResLoadResultNotify();
}

ResInsBase::~ResInsBase()
{
	
}

bool ResInsBase::getIsOrigResNeedImmeUnload()
{
	return this->mIsOrigResNeedImmeUnload;
}

void ResInsBase::setIsOrigResNeedImmeUnload(bool value)
{
	this->mIsOrigResNeedImmeUnload = value;
}

std::string ResInsBase::GetPath()
{
	return this->mPath;
}

std::string ResInsBase::getPrefabName()         // 只有 Prefab 资源才实现这个函数
{
	return "";
}

void ResInsBase::init(ResItem* res)
{
	this->initImpl(res);         // 内部初始化完成后，才分发事件
	this->mRefCountResLoadResultNotify->onLoadEventHandle(this);
}

// 这个是内部初始化实现，初始化都重载这个，但是现在很多都是重在了
void ResInsBase::initImpl(ResItem* res)
{

}

void ResInsBase::failed(ResItem* res)
{
	this->unload();
	this->mRefCountResLoadResultNotify->onLoadEventHandle(this);
}

void ResInsBase::unload()
{

}

void ResInsBase::dispose()
{
	MY_SAFE_DISPOSE(this->mRefCountResLoadResultNotify);
}

RefCountResLoadResultNotify* ResInsBase::getRefCountResLoadResultNotify()
{
	return this->mRefCountResLoadResultNotify;
}

void ResInsBase::setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value)
{
	this->mRefCountResLoadResultNotify = value;
}

std::string ResInsBase::getOrigPath()
{
	return this->mPath;
}

bool ResInsBase::hasSuccessLoaded()
{
	return this->mRefCountResLoadResultNotify->getResLoadState()->hasSuccessLoaded();
}

bool ResInsBase::hasFailed()
{
	return this->mRefCountResLoadResultNotify->getResLoadState()->hasFailed();
}

std::string ResInsBase::getResUniqueId()
{
	return "";
}

MY_END_NAMESPACE