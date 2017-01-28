#include "MyProject.h"
#include "ObjectAssetInsResBase.h"
#include "ResItem.h"
#include "EngineApi.h"
#include "Common.h"
#include "ResInsEventDispatch.h"
#include "MyGameInstanceBase.h"

ObjectAssetInsResBase::ObjectAssetInsResBase()
{
	this->mGo = nullptr;
	this->mRetGO = nullptr;
}

void ObjectAssetInsResBase::initImpl(ResItem* res)
{
	this->mGo = Cast<UClass>(res->getObject(res->getPrefabName()));

	Super::initImpl(res);
}

UObject* ObjectAssetInsResBase::InstantiateObject(std::string resName, bool isSetInitOrientPos, FVector position, FQuat rotation, ResInsEventDispatch* evtHandle)
{
	this->mRetGO = nullptr;

	if (nullptr == this->mGo)
	{
		GLogSys->log("ObjectAssetInsRes::InstantiateObject, Prefab is null");
	}
	else
	{
		this->mRetGO = EngineApi::NewObject<UObject>(EngineApi::GetGameInstance(), Cast<UClass>(this->mGo));

		if (nullptr == mRetGO)
		{
			GLogSys->log("ObjectAssetInsRes::InstantiateObject, Can not instance data");
		}
	}

	if (nullptr != evtHandle)
	{
		evtHandle->dispatchEvent(nullptr);
	}

	return this->mRetGO;
}

UObject* ObjectAssetInsResBase::getObject()
{
	return this->mGo;
}

void ObjectAssetInsResBase::unload()
{
	if (this->mGo != nullptr)
	{
		//UtilApi.UnloadAsset(mGo);      // 强制卸载资源数据
		//UtilApi.DestroyImmediate(mGo, true);
		EngineApi::UnloadUnusedAssets();
		this->mGo = nullptr;
	}

	this->mRetGO = nullptr;

	Super::unload();
}