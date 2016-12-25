#include "MyProject.h"
#include "ObjectAssetLoadItem.h"

ObjectAssetLoadItem::ObjectAssetLoadItem()
{

}

UClass* ObjectAssetLoadItem::getResObj()
{
	return mResObj;
}

void ObjectAssetLoadItem::setResObj(UClass* value)
{
	mResObj = value;
}

void ObjectAssetLoadItem::load()
{
	LoadItem::load();
}

void ObjectAssetLoadItem::unload()
{
	LoadItem::unload();
}