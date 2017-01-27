#include "MyProject.h"
#include "ClassAssetInsRes.h"
#include "ResItem.h"
#include "EngineApi.h"
#include "Common.h"
#include "ResInsEventDispatch.h"

ClassAssetInsRes::ClassAssetInsRes()
{

}

void ClassAssetInsRes::initImpl(ResItem* res)
{
	this->mGo = Cast<UClass>(res->getObject(res->getPrefabName()));

	InsResBase::initImpl(res);
}

UObject* ClassAssetInsRes::InstantiateObject(std::string resName, bool isSetInitOrientPos, FVector position, FQuat rotation, ResInsEventDispatch* evtHandle)
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

UClass* ClassAssetInsRes::getObject()
{
	return this->mGo;
}

void ClassAssetInsRes::unload()
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