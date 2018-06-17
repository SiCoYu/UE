#include "MyProject.h"
#include "AuxLevelLoader.h"
// error C2027: use of undefined type 'LoadParam' ，输出包含目录功能查看，自己头文件 #ifndef __ResLoadPriority_H 写成 #ifndef __LoadParam_H
#include "LoadParam.h"
#include "Prequisites.h"
#include "LevelResItem.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxLevelLoader, AuxLoaderBase)

AuxLevelLoader::AuxLevelLoader()
	: Super()
{
	this->mLevelResItem = nullptr;
}

void AuxLevelLoader::dispose()
{
	Super::dispose();
}

void AuxLevelLoader::syncLoad(
	std::string path, 
	EventDispatchDelegate evtHandle,
	EventDispatchDelegate progressHandle
)
{
	Super::syncLoad(
		path, 
		evtHandle,
		progressHandle
	);

	if (this->isInvalid())
	{
		LoadParam* param = nullptr;
		param = GPoolSys->newObject<LoadParam>();

		param->setPath(this->mPath);
		param->setLoadEventHandle(
			MakeEventDispatchDelegate(
				this, 
				&AuxLevelLoader::onLevelLoaded, 
				0
			)
		);
		param->setIsResNeedCoroutine(false);
		param->setIsLoadNeedCoroutine(false);
		param->setResPackType(ResPackType::eLevelType);
		param->setResLoadType(ResLoadType::eLoadResource);

		GResLoadMgr->loadAsset(param);

		GPoolSys->deleteObj(param);

		this->mLevelResItem = (LevelResItem*)(GResLoadMgr->getResource(param->getResUniqueId()));
		this->onLevelLoaded(this->mLevelResItem);
	}
	else if (this->hasLoadEnd())
	{
		this->onLevelLoaded(this->mLevelResItem);
	}
}

// 异步加载对象
void AuxLevelLoader::asyncLoad(
	std::string path, 
	EventDispatchDelegate evtHandle,
	EventDispatchDelegate progressHandle
)
{
	Super::asyncLoad(
		path, 
		evtHandle, 
		progressHandle
	);

	if (this->isInvalid())
	{
		LoadParam* param = nullptr;
		param = GPoolSys->newObject<LoadParam>();

		param->setPath(this->mPath);
		param->setLoadEventHandle(
			MakeEventDispatchDelegate(
				this, 
				&AuxLevelLoader::onLevelLoaded, 
				0
			)
		);
		param->setIsResNeedCoroutine(true);
		param->setIsLoadNeedCoroutine(true);
		param->setResPackType(ResPackType::eLevelType);
		param->setResLoadType(ResLoadType::eLoadResource);

		GResLoadMgr->loadAsset(param);

		GPoolSys->deleteObj(param);
	}
	else if (this->hasLoadEnd())
	{
		this->onLevelLoaded(this->mLevelResItem);
	}
}

void AuxLevelLoader::onLevelLoaded(IDispatchObject* dispObj, uint eventId)
{
	if (nullptr != dispObj)
	{
		this->mLevelResItem = (LevelResItem*)(dispObj);

		if (this->mLevelResItem->hasSuccessLoaded())
		{
			this->mResLoadState->setSuccessLoaded();
		}
		else if (this->mLevelResItem->hasFailed())
		{
			this->mResLoadState->setFailed();
		}
	}

	if (this->mResEventDispatch != nullptr)
	{
		this->mResEventDispatch->dispatchEvent(this);
	}
}

void AuxLevelLoader::unload()
{
	if (this->mLevelResItem != nullptr)
	{
		GResLoadMgr->unload(
			this->mLevelResItem->getResUniqueId(), 
			nullptr
		);
	}

	Super::unload();
}

MY_END_NAMESPACE