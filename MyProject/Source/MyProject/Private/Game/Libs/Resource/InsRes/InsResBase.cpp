#include "MyProject.h"
#include "InsResBase.h"

InsResBase::InsResBase()
{
#if PKG_RES_LOAD
	m_bOrigResNeedImmeUnload = false;
#else
	m_bOrigResNeedImmeUnload = true;
#endif
	m_refCountResLoadResultNotify = new RefCountResLoadResultNotify();
}

bool InsResBase::getIsOrigResNeedImmeUnload()
{
	return m_bOrigResNeedImmeUnload;
}

void InsResBase::setIsOrigResNeedImmeUnload(bool value)
{
	m_bOrigResNeedImmeUnload = value;
}

std::string InsResBase::GetPath()
{
	return m_path;
}

std::string InsResBase::getPrefabName()         // 只有 Prefab 资源才实现这个函数
{
	return "";
}

void InsResBase::init(ResItem* res)
{
	initImpl(res);         // 内部初始化完成后，才分发事件
	refCountResLoadResultNotify.onLoadEventHandle(this);
}

// 这个是内部初始化实现，初始化都重载这个，但是现在很多都是重在了
void InsResBase::initImpl(ResItem* res)
{

}

void InsResBase::failed(ResItem* res)
{
	unload();
	m_refCountResLoadResultNotify.onLoadEventHandle(this);
}

void InsResBase::unload()
{

}

RefCountResLoadResultNotify* InsResBase::getRefCountResLoadResultNotify()
{
	return m_refCountResLoadResultNotify;
}

void InsResBase::setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value)
{
	m_refCountResLoadResultNotify = value;
}