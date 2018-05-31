#include "MyProject.h"
#include "ObjectAssetResItem.h"
#include "LoadItem.h"
#include "CoreUObject.h"	// UObject
#include "RefCountResLoadResultNotify.h"	// RefCountResLoadResultNotify
#include "ResLoadState.h"
#include "ResEventDispatch.h"

MY_BEGIN_NAMESPACE(MyNS)

ObjectAssetResItem::ObjectAssetResItem()
{
	this->mResObject = nullptr;
}

ObjectAssetResItem::~ObjectAssetResItem()
{
	
}

void ObjectAssetResItem::init(LoadItem* item)
{
	Super::init(item);

	this->mResObject = Cast<UObject>(item->getObject());

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

void ObjectAssetResItem::setPrefabName(std::string prefabName)
{

}

UObject* ObjectAssetResItem::getObject(std::string resName)
{
	return this->mResObject;
}

void ObjectAssetResItem::unload()
{
	
}

MY_END_NAMESPACE