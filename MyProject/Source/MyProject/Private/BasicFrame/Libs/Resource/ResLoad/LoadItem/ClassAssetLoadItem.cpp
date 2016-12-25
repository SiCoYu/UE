#include "MyProject.h"
#include "Common.h"
#include "UObject/Class.h"	// UClass
#include "NonRefCountResLoadResultNotify.h"		// NonRefCountResLoadResultNotify
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

void ClassAssetLoadItem::syncLoad()
{
	mResObj = GMyStreamableManager->SynchronousLoadType<UClass>(this->mPath);

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