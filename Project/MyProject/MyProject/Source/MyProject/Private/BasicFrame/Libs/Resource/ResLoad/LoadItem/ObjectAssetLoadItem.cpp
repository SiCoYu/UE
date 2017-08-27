#include "MyProject.h"
#include "ObjectAssetLoadItem.h"

ObjectAssetLoadItem::ObjectAssetLoadItem()
{
	this->mResObj = nullptr;
}

ObjectAssetLoadItem::~ObjectAssetLoadItem()
{
	
}

UClass* ObjectAssetLoadItem::getResObj()
{
	return this->mResObj;
}

void ObjectAssetLoadItem::setResObj(UClass* value)
{
	this->mResObj = value;
}

void ObjectAssetLoadItem::load()
{
	Super::load();
}

void ObjectAssetLoadItem::unload()
{
	Super::unload();
}