#include "MyProject.h"
#include "ClassAssetResItem.h"
#include "LoadItem.h"
#include "UObject/Class.h"	// UClass
#include "RefCountResLoadResultNotify.h"
#include "ResLoadState.h"
#include "ResEventDispatch.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ClassAssetResItem, ResItem)

ClassAssetResItem::ClassAssetResItem()
{
	this->mResObject = nullptr;
}

ClassAssetResItem::~ClassAssetResItem()
{
	
}

void ClassAssetResItem::initWithLoad(LoadItem* item)
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