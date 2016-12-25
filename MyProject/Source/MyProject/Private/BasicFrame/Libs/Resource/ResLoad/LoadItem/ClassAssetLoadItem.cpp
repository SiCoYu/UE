#include "MyProject.h"
#include "ClassAssetLoadItem.h"

ClassAssetLoadItem::ClassAssetLoadItem()
{

}

UClass* ClassAssetLoadItem::getResObj()
{
	return mResObj;
}

void ClassAssetLoadItem::setResObj(UClass* value)
{
	mResObj = value;
}

void ClassAssetLoadItem::load()
{
	LoadItem::load();
}

void ClassAssetLoadItem::unload()
{
	LoadItem::unload();
}