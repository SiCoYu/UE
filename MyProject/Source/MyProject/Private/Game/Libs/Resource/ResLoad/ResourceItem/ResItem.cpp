#include "MyProject.h"
#include "ResItem.h"
#include "RefCountResLoadResultNotify.h"

ResItem::ResItem()
{
	m_refCountResLoadResultNotify = new RefCountResLoadResultNotify();
}

ResPackType ResItem::getResPackType()
{
	return m_resPackType;
}

ResPackType ResItem::getResPackType()
{
	return m_resPackType;
}

void ResItem::setResPackType(ResPackType value)
{
	m_resPackType = value;
}

std::string ResItem::getPath()
{
	return m_path;
}

void ResItem::setPath(std::string value)
{
	m_path = value;
}

std::string ResItem::getPathNoExt()
{
	return m_pathNoExt;
}

void ResItem::setPathNoExt(std::string value)
{
	m_pathNoExt = value;
}

std::string ResItem::getExtName()
{
	return m_extName;
}

void ResItem::setExtName(std::string value)
{
	m_extName = value;
}

std::string ResItem::getPath()
{
	return m_path;
}

ResLoadType ResItem::getResLoadType()
{
	return m_resLoadType;
}

void ResItem::setResLoadType(ResLoadType value)
{
	m_resLoadType = value;
}

RefCountResLoadResultNotify* ResItem::getRefCountResLoadResultNotify()
{
	return m_refCountResLoadResultNotify;
}

void ResItem::setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value)
{
	m_refCountResLoadResultNotify = value;
}

std::string ResItem::getPrefabName()         // 只有 Prefab 资源才实现这个函数
{
	return "";
}

void ResItem::init(LoadItem* item)
{
	m_refCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
}

void ResItem::failed(LoadItem* item)
{
	m_refCountResLoadResultNotify->getResLoadState()->setFailed();
	m_refCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

void ResItem::reset()
{
	m_path = "";
	m_refCountResLoadResultNotify->getResLoadState()->reset();
	m_refCountResLoadResultNotify->getRefCount()->setRefNum(0);
}

// 卸载
void ResItem::unload()
{

}

GameObject ResItem::InstantiateObject(std::string resName)
{
	return nullptr;
}

UnityEngine.Object ResItem::getObject(string resName)
{
	return nullptr;
}

byte[] ResItem::getBytes(string resName)            // 获取字节数据
{
	return null;
}

std::string ResItem::getText(std::string resName)
{
	return null;
}

void ResItem::copyFrom(ResItem rhv)
{
	m_resPackType = rhv.m_resPackType;
	m_resLoadType = rhv.m_resLoadType;
	m_path = rhv.m_path;
	m_pathNoExt = rhv.m_pathNoExt;
	m_extName = rhv.m_extName;
	m_resNeedCoroutine = rhv.m_resNeedCoroutine;
	m_refCountResLoadResultNotify.copyFrom(rhv.refCountResLoadResultNotify);
}