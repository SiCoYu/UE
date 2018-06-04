#include "MyProject.h"
#include "ClassAssetLoadItem.h"
#include "Prequisites.h"
#include "UObject/Class.h"	// UClass
#include "NonRefCountResLoadResultNotify.h"		// NonRefCountResLoadResultNotify
#include "UtilEngineWrap.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ClassAssetLoadItem, LoadItem)

ClassAssetLoadItem::ClassAssetLoadItem()
{
	this->mResObject = nullptr;
}

ClassAssetLoadItem::~ClassAssetLoadItem()
{
	
}

UObject* ClassAssetLoadItem::getObject()
{
	return this->mResObject;
}

void ClassAssetLoadItem::setObject(UObject* value)
{
	this->mResObject = Cast<UClass>(value);
}

void ClassAssetLoadItem::syncLoad()
{
	this->mResObject = GMyStreamableManager->SynchronousLoadType<UClass>(this->mPath);

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

void ClassAssetLoadItem::asyncLoad()
{
	this->mAssetRef.SetPath(UtilStr::ConvStdStr2FString(const_cast<std::string&>(this->mPath)));

	GMyStreamableManager->RequestAsyncLoad(this->mAssetRef, FStreamableDelegate::CreateRaw(this, &ClassAssetLoadItem::onAsyncLoaded));
}

void ClassAssetLoadItem::onAsyncLoaded()
{
	//this->mResObject = Cast<UClass>GMyStreamableManager->GetStreamed(this->mPath);
	//this->mResObject = Cast<UClass>(this->mAssetRef.ResolveObject());
	// Engine\Source\Runtime\GameplayAbilities\Private\GameplayCueManager.cpp
	// OnGameplayCueNotifyAsyncLoadComplete
	this->mResObject = UtilEngineWrap::FindObject<UClass>(nullptr, *this->mAssetRef.ToString());

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

void ClassAssetLoadItem::load()
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

void ClassAssetLoadItem::unload()
{
	Super::unload();
}

MY_END_NAMESPACE