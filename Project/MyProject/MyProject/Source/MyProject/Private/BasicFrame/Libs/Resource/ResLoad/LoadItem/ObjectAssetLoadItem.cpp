#include "MyProject.h"
#include "ObjectAssetLoadItem.h"

ObjectAssetLoadItem::ObjectAssetLoadItem()
{
	this->mResObject = nullptr;
}

ObjectAssetLoadItem::~ObjectAssetLoadItem()
{
	
}

UClass* ObjectAssetLoadItem::getObject()
{
	return this->mResObject;
}

void ObjectAssetLoadItem::setObject(UObject* value)
{
	this->mResObject = value;
}

void ObjectAssetLoadItem::syncLoad()
{
	this->mResObject = GMyStreamableManager->SynchronousLoadType<UObject>(this->mPath);

	if (nullptr != mResObject)
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
	}
	else
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setFailed();
	}

	this->mNonRefCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

void ObjectAssetLoadItem::asyncLoad()
{
	this->mAssetRef.SetPath(UtilStr::ConvStdStr2FString(const_cast<std::string&>(this->mPath)));

	GMyStreamableManager->RequestAsyncLoad(this->mAssetRef, FStreamableDelegate::CreateRaw(this, &ClassAssetLoadItem::onAsyncLoaded));
}

void ObjectAssetLoadItem::onAsyncLoaded()
{
	//this->mResObject = Cast<UClass>GMyStreamableManager->GetStreamed(this->mPath);
	//this->mResObject = Cast<UClass>(mAssetRef.ResolveObject());
	// Engine\Source\Runtime\GameplayAbilities\Private\GameplayCueManager.cpp
	// OnGameplayCueNotifyAsyncLoadComplete
	this->mResObject = UtilEngineWrap::FindObject<UObject>(nullptr, *this->mAssetRef.ToString());

	//if (nullptr != this->mResObject)
	if (ensure(this->mResObject))
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
	}
	else
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setFailed();
	}

	this->mNonRefCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

void ObjectAssetLoadItem::load()
{
	Super::load();

	if (!this->getLoadNeedCoroutine())
	{
		this->syncLoad();
	}
	else
	{
		this->asyncLoad();
	}
}

void ObjectAssetLoadItem::unload()
{
	Super::unload();
}