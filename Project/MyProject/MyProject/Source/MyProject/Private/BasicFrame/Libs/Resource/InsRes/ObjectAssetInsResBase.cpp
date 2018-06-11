#include "MyProject.h"
#include "ObjectAssetInsResBase.h"
#include "ResItem.h"
#include "UtilEngineWrap.h"
#include "Prequisites.h"
#include "ResInsEventDispatch.h"
#include "MyGameInstanceBase.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ObjectAssetInsResBase, ResInsBase)

ObjectAssetInsResBase::ObjectAssetInsResBase()
{
	this->mActor = nullptr;
	this->mRetActor = nullptr;
}

ObjectAssetInsResBase::~ObjectAssetInsResBase()
{
	
}

void ObjectAssetInsResBase::initImpl(ResItem* res)
{
	this->mActor = Cast<UClass>(res->getObject(res->getPrefabName()));

	Super::initImpl(res);
}

UObject* ObjectAssetInsResBase::InstantiateObject(std::string resName, bool isSetInitOrientPos, FVector position, FQuat rotation, ResInsEventDispatch* evtHandle)
{
	this->mRetActor = nullptr;

	if (nullptr == this->mActor)
	{
		GLogSys->log("ObjectAssetInsRes::InstantiateObject, Prefab is nullptr");
	}
	else
	{
		this->mRetActor = UtilEngineWrap::NewObject<UObject>(UtilEngineWrap::GetGameInstance(), Cast<UClass>(this->mActor));

		if (nullptr == mRetActor)
		{
			GLogSys->log("ObjectAssetInsRes::InstantiateObject, Can not instance data");
		}
	}

	if (nullptr != evtHandle)
	{
		evtHandle->dispatchEvent(nullptr);
	}

	return this->mRetActor;
}

UObject* ObjectAssetInsResBase::getObject()
{
	return this->mActor;
}

UClass* ObjectAssetInsResBase::getClass()
{
	return Cast<UClass>(this->mActor);
}

void ObjectAssetInsResBase::unload()
{
	if (this->mActor != nullptr)
	{
		//UtilSysLibWrap.UnloadAsset(mActor);      // 强制卸载资源数据
		//UtilSysLibWrap.DestroyImmediate(mActor, true);
		UtilEngineWrap::UnloadUnusedAssets();
		this->mActor = nullptr;
	}

	this->mRetActor = nullptr;

	Super::unload();
}

MY_END_NAMESPACE