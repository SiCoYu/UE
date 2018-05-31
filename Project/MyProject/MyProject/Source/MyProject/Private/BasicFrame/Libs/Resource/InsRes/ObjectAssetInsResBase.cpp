#include "MyProject.h"
#include "ObjectAssetInsResBase.h"
#include "ResItem.h"
#include "UtilEngineWrap.h"
#include "Prequisites.h"
#include "ResInsEventDispatch.h"
#include "MyGameInstanceBase.h"

MY_BEGIN_NAMESPACE(MyNS)

ObjectAssetInsResBase::ObjectAssetInsResBase()
{
	this->mGo = nullptr;
	this->mRetGO = nullptr;
}

ObjectAssetInsResBase::~ObjectAssetInsResBase()
{
	
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
		this->mRetGO = UtilEngineWrap::NewObject<UObject>(UtilEngineWrap::GetGameInstance(), Cast<UClass>(this->mGo));

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

UClass* ObjectAssetInsResBase::getClass()
{
	return Cast<UClass>(this->mGo);
}

void ObjectAssetInsResBase::unload()
{
	if (this->mGo != nullptr)
	{
		//UtilSysLibWrap.UnloadAsset(mGo);      // 强制卸载资源数据
		//UtilSysLibWrap.DestroyImmediate(mGo, true);
		UtilEngineWrap::UnloadUnusedAssets();
		this->mGo = nullptr;
	}

	this->mRetGO = nullptr;

	Super::unload();
}

MY_END_NAMESPACE