#include "MyProject.h"
#include "LoadItem.h"
#include "NonRefCountResLoadResultNotify.h"

LoadItem::LoadItem()
{
	m_nonRefCountResLoadResultNotify = new NonRefCountResLoadResultNotify();
}

ResPackType LoadItem::getResPackType()
{
	return m_resPackType;
}

void LoadItem::setResPackType(ResPackType value)
{
	m_resPackType = value;
}

std::string LoadItem::getPath()
{
	return m_path;
}

void LoadItem::setPath(std::string value)
{
	m_path = value;
}

std::string LoadItem::getPathNoExt()
{
	return m_pathNoExt;
}

void LoadItem::setPathNoExt(std::string value)
{
	m_pathNoExt = value;
}

std::string LoadItem::getExtName()
{
	return m_extName;
}

void LoadItem::setExtName(std::string value)
{
	m_extName = value;
}

ResLoadType LoadItem::getResLoadType()
{
	return m_resLoadType;
}

void LoadItem::setResLoadType(ResLoadType value)
{
	m_resLoadType = value;
}

NonRefCountResLoadResultNotify* LoadItem::getNonRefCountResLoadResultNotify()
{
	return m_nonRefCountResLoadResultNotify;
}

void LoadItem::setNonRefCountResLoadResultNotify(NonRefCountResLoadResultNotify* value)
{
	m_nonRefCountResLoadResultNotify = value;
}

void LoadItem::load()
{
	m_nonRefCountResLoadResultNotify->getResLoadState()->setLoading();
}

// 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
void LoadItem::unload()
{

}

void LoadItem::reset()
{
	m_path = "";
	m_loadNeedCoroutine = false;
}