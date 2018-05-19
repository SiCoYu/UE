#include "MyProject.h"
#include "LevelLoadItem.h"
#include "ResLoadType.h"
#include "UtilEngineWrap.h"
#include "Common.h"
#include "UtilEngineWrap.h"
#include "MyDelegateDef.h"
#include "ResEventDispatch.h"
#include "NonRefCountResLoadResultNotify.h"
#include "ResLoadState.h"
#include "MyDelegateLevelLoad.h"

LevelLoadItem::LevelLoadItem()
{
	this->mMyDelegateLevelLoad = nullptr;
	//this->mOnLevelLoadDelegate = nullptr;
	//this->mOnLevelLoadDelegateHandle = nullptr;
}

LevelLoadItem::~LevelLoadItem()
{

}

void LevelLoadItem::setLevelName(std::string levelName)
{
	this->mLevelName = levelName;
}

std::string LevelLoadItem::getLevelName()
{
	return this->mLevelName;
}

void LevelLoadItem::reset()
{
	//if (nullptr != this->mOnLevelLoadDelegate && nullptr != this->mOnLevelLoadDelegateHandle)
	//if (nullptr != this->mOnLevelLoadDelegate)
	{
		//this->mOnLevelLoadDelegate.Remove(this->mOnLevelLoadDelegateHandle);
		this->mMyDelegateLevelLoad->mMyDelegateBaseEvent.Unbind();
	}
}

void LevelLoadItem::load()
{
	Super::load();

	if (nullptr == this->mMyDelegateLevelLoad)
	{
		this->mMyDelegateLevelLoad = UtilEngineWrap::NewObject<UMyDelegateLevelLoad>();
		//this->mMyDelegateLevelLoad->Add
	}

	//this->mOnLevelLoadDelegate = FMyDelegateDef::MyDelegateBaseHandle::CreateRaw(this, &LevelLoadItem::assetAssetBundlesLevelLoaded);
	//this->mOnLevelLoadDelegateHandle = this->mOnLevelLoadDelegate.Add(this->mOnLevelLoadDelegate);
	this->mMyDelegateLevelLoad->mMyDelegateBaseEvent.BindRaw(this, &LevelLoadItem::assetAssetBundlesLevelLoaded);

	if (eLoadResource == this->mResLoadType ||
		eLoadStreamingAssets == mResLoadType ||
		eLoadPersistentData == mResLoadType)
	{
		// 需要加载 AssetBundles 加载
		if (this->mIsLoadNeedCoroutine)
		{
			this->loadFromAssetBundleByCoroutine();
		}
		else
		{
			this->loadFromAssetBundle();
		}
	}
	else if (eLoadWeb == mResLoadType)
	{
		//Ctx.mInstance.mCoroutineMgr.StartCoroutine(downloadAsset());
	}
}

void LevelLoadItem::unload()
{
	Super::unload();
}

// StreamLevel 需要制作 StreamLevel 才行，不是随便一个关卡就能加载的
void LevelLoadItem::loadFromAssetBundleByCoroutine()
{
	FLatentActionInfo info;
	info.ExecutionFunction = "onLevelLoaded";
	info.CallbackTarget = this->mMyDelegateLevelLoad;
	info.UUID = 0;
	// Linkage 一定要有值，具体参考
	// Engine\Source\Runtime\Engine\Private\LevelStreaming.cpp
	// Response.FinishAndTriggerIf(bIsOperationFinished, LatentInfo.ExecutionFunction, LatentInfo.Linkage, LatentInfo.CallbackTarget);
	// Engine\Source\Runtime\Engine\Private\LatentActionManager.cpp
	// if (LinkInfo.LinkID != INDEX_NONE)
	// LoadStreamLevel ignores LatentActionInfo
	// https://answers.unrealengine.com/questions/241954/loadstreamlevel-ignores-latentactioninfo.html
	info.Linkage = 0;

	UtilEngineWrap::LoadStreamLevel(GEngineData->getMainActor(), this->mLevelName, true, false, info);
	//UtilEngineWrap::SetClientTravel(UtilEngineWrap::GetWorld(), TEXT("/Game/MyAsset/Map/TestMap2"), TRAVEL_Absolute);
	//UtilEngineWrap::ServerTravel(TEXT("/Game/MyAsset/Map/TestMap2?game=TDM?listen"));
}

void LevelLoadItem::loadFromAssetBundle()
{
	UtilEngineWrap::OpenLevel(GEngineData->getMainActor(), this->mLevelName, true, "");
}

void LevelLoadItem::assetAssetBundlesLevelLoaded(IDispatchObject* dispObj)
{
	//if (this->mAssetBundle != nullptr)
	if(true)
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setSuccessLoaded();
	}
	else
	{
		this->mNonRefCountResLoadResultNotify->getResLoadState()->setFailed();
	}

	this->mNonRefCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}