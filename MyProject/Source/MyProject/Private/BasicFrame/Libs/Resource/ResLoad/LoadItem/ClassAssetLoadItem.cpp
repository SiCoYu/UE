#include "MyProject.h"
#include "Common.h"
#include "UObject/Class.h"	// UClass
#include "NonRefCountResLoadResultNotify.h"		// NonRefCountResLoadResultNotify
#include "ClassAssetLoadItem.h"

ClassAssetLoadItem::ClassAssetLoadItem()
{
	this->mResObj = nullptr;
}

UObject* ClassAssetLoadItem::getObject()
{
	return this->mResObj;
}

void ClassAssetLoadItem::setObject(UObject* value)
{
	this->mResObj = Cast<UClass>(value);
}

void ClassAssetLoadItem::syncLoad()
{
	this->mResObj = GMyStreamableManager->SynchronousLoadType<UClass>(this->mPath);

	if (nullptr != mResObj)
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
	}
	else
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setFailed();
	}

	this->mNonRefCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

void ClassAssetLoadItem::asyncLoad()
{

}

void ClassAssetLoadItem::load()
{
	LoadItem::load();

	if (!this->getLoadNeedCoroutine())
	{
		this->syncLoad();
	}
	else
	{
		this->asyncLoad();
	}
}

void ClassAssetLoadItem::unload()
{
	LoadItem::unload();
}