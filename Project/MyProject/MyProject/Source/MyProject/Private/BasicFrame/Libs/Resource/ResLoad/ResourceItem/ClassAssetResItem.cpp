#include "MyProject.h"
#include "ClassAssetResItem.h"
#include "LoadItem.h"
#include "UObject/Class.h"	// UClass
#include "RefCountResLoadResultNotify.h"
#include "ResLoadState.h"
#include "ResEventDispatch.h"

MY_BEGIN_NAMESPACE(MyNS)

ClassAssetResItem::ClassAssetResItem()
{
	this->mResObject = nullptr;
}

ClassAssetResItem::~ClassAssetResItem()
{
	
}

void ClassAssetResItem::init(LoadItem* item)
{
	Super::init(item);

	this->mResObject = Cast<UClass>(item->getObject());

	if (nullptr != this->mResObject)
	{
		this->mRefCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
	}
	else
	{
		this->mRefCountResLoadResultNotify->getResLoadState()->setFailed();
	}

	this->mRefCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

void ClassAssetResItem::setPrefabName(std::string prefabName)
{

}

UObject* ClassAssetResItem::getObject(std::string resName)
{
	return this->mResObject;
}

void ClassAssetResItem::unload()
{

}

MY_END_NAMESPACE