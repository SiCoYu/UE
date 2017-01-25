#include "MyProject.h"
#include "AuxLevelLoader.h"
#include "LoadParam.h"
#include "Common.h"

namespace MyNS
{
	AuxLevelLoader::AuxLevelLoader(std::string path)
		: Super(path)
	{

	}

	void AuxLevelLoader::dispose()
	{
		Super::dispose();
	}

	void AuxLevelLoader::syncLoad(std::string path, EventDispatchDelegate evtHandle)
	{
		Super::syncLoad(path, evtHandle);

		if (this->isInvalid())
		{
			LoadParam* param;
			param = GPoolSys->newObject<LoadParam>();
			param->setPath(mPath);
			param->mLoadEventHandle = onLevelLoaded;
			param->mResNeedCoroutine = false;
			param->mLoadNeedCoroutine = false;
			GResLoadMgr->loadAsset(param);
			GPoolSys->deleteObj(param);

			this->mLevelResItem = (LevelResItem*)(GResLoadMgr->getResource(param->mResUniqueId));
			this->onLevelLoaded(this->mLevelResItem);
		}
		else if (this->hasLoadEnd())
		{
			this->onLevelLoaded(this->mLevelResItem);
		}
	}

	// 异步加载对象
	void AuxLevelLoader::asyncLoad(std::string path, EventDispatchDelegate evtHandle)
	{
		Super::asyncLoad(path, evtHandle);

		if (this->isInvalid())
		{
			LoadParam* param;
			param = GPoolSys->newObject<LoadParam>();
			param->setPath(mPath);
			param->mLoadEventHandle = this.onLevelLoaded;
			param->mResNeedCoroutine = true;
			param->mLoadNeedCoroutine = true;
			GResLoadMgr->loadAsset(param);
			GPoolSys->deleteObj(param);
		}
		else if (this->hasLoadEnd())
		{
			this->onLevelLoaded(this->mLevelResItem);
		}
	}

	void AuxLevelLoader::onLevelLoaded(IDispatchObject* dispObj)
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

		if (this->mEvtHandle != nullptr)
		{
			this->mEvtHandle->dispatchEvent(this);
		}
	}

	void AuxLevelLoader::unload()
	{
		if (this->mLevelResItem != nullptr)
		{
			GResLoadMgr->unload(mLevelResItem.getResUniqueId(), nullptr);
			Super::unload();
		}
	}
}