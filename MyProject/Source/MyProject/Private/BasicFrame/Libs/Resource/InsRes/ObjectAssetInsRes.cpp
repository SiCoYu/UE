#include "MyProject.h"
#include "ResItem.h"
#include "EngineApi.h"
#include "Common.h"
#include "ObjectAssetInsRes.h"

ObjectAssetInsRes::ObjectAssetInsRes()
{

}

void ObjectAssetInsRes::initImpl(ResItem* res)
{
	//mGo = res.getObject(res.getPrefabName()) as GameObject;
	//base.initImpl(res);
}

UObject* ObjectAssetInsRes::InstantiateObject(std::string resName)
{
	mRetGO = nullptr;

	if (nullptr == mGo)
	{
		GLogSys->log("Prefab is null");
	}
	else
	{
		// mRetGO = GameObject.Instantiate(mGo) as GameObject;
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