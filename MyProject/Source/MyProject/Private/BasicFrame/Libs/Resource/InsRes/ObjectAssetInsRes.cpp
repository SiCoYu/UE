#include "MyProject.h"
#include "ObjectAssetInsRes.h"
#include "ResItem.h"
#include "EngineApi.h"
#include "Common.h"
#include "ResInsEventDispatch.h"
#include "MyGameInstanceBase.h"

ObjectAssetInsRes::ObjectAssetInsRes()
{
	this->mGo = nullptr;
	this->mRetGO = nullptr;
}

void ObjectAssetInsRes::initImpl(ResItem* res)
{
	//mGo = res.getObject(res.getPrefabName()) as GameObject;
	//base.initImpl(res);
}

UObject* ObjectAssetInsRes::InstantiateObject(std::string resName, bool isSetInitOrientPos, FVector position, FQuat rotation, ResInsEventDispatch* evtHandle)
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

UObject* ObjectAssetInsRes::getObject()
{
	return this->mGo;
}

void ObjectAssetInsRes::unload()
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