#include "MyProject.h"
#include "ObjectAssetInsRes.h"
#include "ResItem.h"
#include "EngineApi.h"
#include "Common.h"
#include "ResInsEventDispatch.h"

ObjectAssetInsRes::ObjectAssetInsRes()
{

}

void ObjectAssetInsRes::initImpl(ResItem* res)
{
	//mGo = res.getObject(res.getPrefabName()) as GameObject;
	//base.initImpl(res);
}

UObject* ObjectAssetInsRes::InstantiateObject(std::string resName, bool isSetInitOrientPos, FVector position, FQuat rotation, ResInsEventDispatch* evtHandle)
{
	mRetGO = nullptr;

	if (nullptr == mGo)
	{
		GLogSys->log("Prefab is null");
	}
	else
	{
		mRetGO = EngineApi::NewObject<UObject>(EngineApi::GetGameInstance(), mGo);

		if (nullptr == mRetGO)
		{
			GLogSys->log("Can not instance data");
		}
	}
	return mRetGO;
}

UObject* ObjectAssetInsRes::getObject()
{
	return mGo;
}

void ObjectAssetInsRes::unload()
{
	if (mGo != nullptr)
	{
		//UtilApi.UnloadAsset(mGo);      // 强制卸载资源数据
		//UtilApi.DestroyImmediate(mGo, true);
		EngineApi::UnloadUnusedAssets();
		mGo = nullptr;
	}
	mRetGO = nullptr;
	InsResBase::unload();
}