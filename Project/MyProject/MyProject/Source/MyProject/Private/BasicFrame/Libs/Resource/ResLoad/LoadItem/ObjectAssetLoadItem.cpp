#include "MyProject.h"
#include "ObjectAssetLoadItem.h"
#include "Prequisites.h"
#include "CoreUObject.h"	// UObject
#include "NonRefCountResLoadResultNotify.h"		// NonRefCountResLoadResultNotify
#include "UtilEngineWrap.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ObjectAssetLoadItem, LoadItem)

ObjectAssetLoadItem::ObjectAssetLoadItem()
{
	this->mResObject = nullptr;
}

ObjectAssetLoadItem::~ObjectAssetLoadItem()
{
	
}

UObject* ObjectAssetLoadItem::getObject()
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

	if (nullptr != this->mResObject)
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

	GMyStreamableManager->RequestAsyncLoad(this->mAssetRef, FStreamableDelegate::CreateRaw(this, &ObjectAssetLoadItem::onAsyncLoaded));
}

void ObjectAssetLoadItem::onAsyncLoaded()
{
	//this->mResObject = Cast<UClass>GMyStreamableManager->GetStreamed(this->mPath);
	//this->mResObject = Cast<UClass>(this->mAssetRef.ResolveObject());
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

MY_END_NAMESPACE