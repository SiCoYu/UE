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

std::string getPath()
{
	return m_path;
}

void setPath(std::string value)
{
	m_path = value;
}

std::string getPathNoExt()
{
	return m_pathNoExt;
}

void setPathNoExt(std::string value)
{
	m_pathNoExt = value;
}

std::string getExtName()
{
	return m_extName;
}

void setExtName(std::string value)
{
	m_extName = value;
}

std::string getPath()
{
	return m_path;
}

ResLoadType getResLoadType()
{
	return m_resLoadType;
}

void setResLoadType(ResLoadType value)
{
	m_resLoadType = value;
}

RefCountResLoadResultNotify* getRefCountResLoadResultNotify()
{
	return m_refCountResLoadResultNotify;
}

void setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value)
{
	m_refCountResLoadResultNotify = value;
}

virtual std::string getPrefabName()         // 只有 Prefab 资源才实现这个函数
{
	return "";
}

virtual void init(LoadItem* item)
{
	m_refCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
}

virtual void failed(LoadItem* item)
{
	m_refCountResLoadResultNotify->getResLoadState()->setFailed();
	m_refCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

virtual void reset()
{
	m_path = "";
	m_refCountResLoadResultNotify->getResLoadState()->reset();
	m_refCountResLoadResultNotify->getRefCount()->setRefNum(0);
}

// 卸载
virtual void unload()
{

}

virtual GameObject InstantiateObject(std::string resName)
{
	return nullptr;
}

virtual UnityEngine.Object getObject(string resName)
{
	return nullptr;
}

virtual byte[] getBytes(string resName)            // 获取字节数据
{
	return null;
}

virtual string getText(string resName)
{
	return null;
}

void copyFrom(ResItem rhv)
{
	m_resPackType = rhv.m_resPackType;
	m_resLoadType = rhv.m_resLoadType;
	m_path = rhv.m_path;
	m_pathNoExt = rhv.m_pathNoExt;
	m_extName = rhv.m_extName;
	m_resNeedCoroutine = rhv.m_resNeedCoroutine;
	m_refCountResLoadResultNotify.copyFrom(rhv.refCountResLoadResultNotify);
}