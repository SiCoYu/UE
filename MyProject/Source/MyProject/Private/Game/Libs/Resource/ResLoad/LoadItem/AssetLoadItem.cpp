#include "MyProject.h"
#include "AssetLoadItem.h"

AssetLoadItem::AssetLoadItem()
{

}

UClass* AssetLoadItem::getResObj()
{
	return m_resObj;
}

void AssetLoadItem::setResObj(UClass* value)
{
	m_resObj = value;
}

void AssetLoadItem::load()
{
	LoadItem::load();
}

void AssetLoadItem::unload()
{
	LoadItem::unload();
}