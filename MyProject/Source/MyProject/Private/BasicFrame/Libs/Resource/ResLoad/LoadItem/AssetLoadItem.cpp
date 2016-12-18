#include "MyProject.h"
#include "AssetLoadItem.h"

AssetLoadItem::AssetLoadItem()
{

}

UClass* AssetLoadItem::getResObj()
{
	return mResObj;
}

void AssetLoadItem::setResObj(UClass* value)
{
	mResObj = value;
}

void AssetLoadItem::load()
{
	LoadItem::load();
}

void AssetLoadItem::unload()
{
	LoadItem::unload();
}