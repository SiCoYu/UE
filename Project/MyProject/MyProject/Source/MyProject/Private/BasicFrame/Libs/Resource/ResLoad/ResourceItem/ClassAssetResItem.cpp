#include "MyProject.h"
#include "LoadItem.h"
#include "UObject/Class.h"	// UClass
#include "RefCountResLoadResultNotify.h"
#include "ResLoadState.h"
#include "ResEventDispatch.h"
#include "ClassAssetResItem.h"

ClassAssetResItem::ClassAssetResItem()
{
	this->mResObj = nullptr;
}

ClassAssetResItem::~ClassAssetResItem()
{
	
}

void ClassAssetResItem::init(LoadItem* item)
{
	Super::init(item);

	this->mResObj = Cast<UClass>(item->getObject());

	if (nullptr != this->mResObj)
	{
		this->mRefCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
	}
	else
	{
		this->mRefCountResLoadResultNotify->getResLoadState()->setFailed();
	}

	this->mRefCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

UObject* ClassAssetResItem::getObject(std::string resName)
{
	return this->mResObj;
}

void ClassAssetResItem::unload()
{

}

void ClassAssetResItem::setPrefabName(std::string prefabName)
{

}