#include "MyProject.h"
#include "ClassAssetInsRes.h"
#include "ResItem.h"
#include "EngineApi.h"
#include "Common.h"
#include "ResInsEventDispatch.h"
#include "MyGameInstanceBase.h"

ClassAssetInsRes::ClassAssetInsRes()
{
	this->mGo = nullptr;
	this->mRetGO = nullptr;
}

void ClassAssetInsRes::initImpl(ResItem* res)
{
	this->mGo = Cast<UClass>(res->getObject(res->getPrefabName()));

	Super::initImpl(res);
}

UObject* ClassAssetInsRes::InstantiateObject(std::string resName, bool isSetInitOrientPos, FVector position, FQuat rotation, ResInsEventDispatch* evtHandle)
{
	this->mRetGO = nullptr;

	if (nullptr == this->mGo)
	{
		GLogSys->log("Prefab is null");
	}
	else
	{
		this->mRetGO = EngineApi::NewObject<UObject>(EngineApi::GetGameInstance(), this->mGo);

		if (nullptr == this->mRetGO)
		{
			GLogSys->log("Can not instance data");
		}
	}

	if (nullptr != evtHandle)
	{
		evtHandle->dispatchEvent(nullptr);
	}

	return this->mRetGO;
}

UClass* ClassAssetInsRes::getObject()
{
	return this->mGo;
}

void ClassAssetInsRes::unload()
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