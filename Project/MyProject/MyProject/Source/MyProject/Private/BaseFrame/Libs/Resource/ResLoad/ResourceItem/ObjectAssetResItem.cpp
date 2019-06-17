#include "MyProject.h"
#include "ObjectAssetResItem.h"
#include "LoadItem.h"
#include "CoreUObject.h"	// UObject
#include "RefCountResLoadResultNotify.h"	// RefCountResLoadResultNotify
#include "ResLoadState.h"
#include "ResEventDispatch.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ObjectAssetResItem, ResItem)

ObjectAssetResItem::ObjectAssetResItem()
{
	this->mResObject = nullptr;
}

ObjectAssetResItem::~ObjectAssetResItem()
{
	
}

void ObjectAssetResItem::initWithLoad(LoadItem* item)
{
	Super::initWithLoad(item);

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