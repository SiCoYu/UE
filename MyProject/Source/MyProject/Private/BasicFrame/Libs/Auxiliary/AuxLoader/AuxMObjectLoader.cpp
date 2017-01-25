#include "MyProject.h"
#include "AuxPrefabLoader.h"

AuxPrefabLoader::AuxPrefabLoader(std::string path, bool isNeedInsPrefab, bool isInsNeedCoroutine)
	: Super(path)
{
	this->mIsInsNeedCoroutine = isInsNeedCoroutine;
	this->mIsDestroySelf = true;
	this->mIsNeedInsPrefab = isNeedInsPrefab;

	this->mIsSetInitOrientPos = false;
	this->mIsSetFakePos = false;
}

void AuxPrefabLoader::setIsInitOrientPos(bool isSet)
{
	this->mIsSetInitOrientPos = isSet;
}

void AuxPrefabLoader::setIsFakePos(bool isSet)
{
	this->mIsSetFakePos = isSet;
}

void AuxPrefabLoader::dispose()
{
	if (this->mIsDestroySelf)
	{
		if (this->mSelfGo != null)
		{
			//UtilApi.DestroyImmediate(this.mSelfGo);
		}
	}

	Super::dispose();
}

UObject* AuxPrefabLoader::getSelfGo()
{
	return this->mSelfGo;
}

void AuxPrefabLoader::setSelfGo(UObject* value)
{
	this->mSelfGo = value;
}

bool AuxPrefabLoader::isDestroySelf()
{
	return this->mIsDestroySelf;
}

void AuxPrefabLoader::setDestroySelf(bool value)
{
	this->mIsDestroySelf = value;
}

std::string AuxPrefabLoader::getLogicPath()
{
	if (this->mPrefabRes != nullptr)
	{
		return this->mPrefabRes->getLogicPath();
	}

	return this->mPath;
}

void AuxPrefabLoader::syncLoad(std::string path, MAction<IDispatchObject> evtHandle)
{
	Super::syncLoad(path, evtHandle);

	if (this->isInvalid())
	{
		this->mPrefabRes = GObjectAssetInsMgr->getAndSyncLoadRes(path, nullptr);
		this->onPrefabLoaded(mPrefabRes);
	}
	else if (this->hasLoadEnd())
	{
		this->onPrefabLoaded(mPrefabRes);
	}
}

// 异步加载对象
void AuxPrefabLoader::asyncLoad(std::string path, EventDispatchDelegate evtHandle)
{
	Super::asyncLoad(path, evtHandle);

	if (this->isInvalid())
	{
		this->mPrefabRes = GObjectAssetInsMgr->getAndAsyncLoadRes(path, AuxPrefabLoader::onPrefabLoaded);
	}
	else if (this.hasLoadEnd())
	{
		this.onPrefabLoaded(this.mPrefabRes);
	}
}

void AuxPrefabLoader::onPrefabLoaded(IDispatchObject* dispObj)
{
	if (nullptr != dispObj)
	{
		// 一定要从这里再次取值，因为如果这个资源已经加载，可能在返回之前就先调用这个函数，因此这个时候 mPrefabRes 还是空值
		this->mPrefabRes = (PrefabRes*)dispObj;

		if (this->mPrefabRes->hasSuccessLoaded())
		{
			this->mResLoadState->setSuccessLoaded();

			if (this->mIsNeedInsPrefab)
			{
				if (this->mIsInsNeedCoroutine)
				{
					this->mResInsEventDispatch = new ResInsEventDispatch();
					this->mResInsEventDispatch->addEventHandle(nullptr, onPrefabIns);

					if (this->mIsSetFakePos)
					{
						this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilApi.FAKE_POS, UtilMath.UnitQuat, this->mResInsEventDispatch);
					}
					else
					{
						this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilMath.ZeroVec3, UtilMath.UnitQuat, this->mResInsEventDispatch);
					}
				}
				else
				{
					if (this->mIsSetFakePos)
					{
						this->setSelfGo(this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilApi.FAKE_POS, UtilMath.UnitQuat));
					}
					else
					{
						this->setSelfGo(this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilMath.ZeroVec3, UtilMath.UnitQuat));
					}

					this->onAllFinish();
				}
			}
			else
			{
				this->onAllFinish();
			}
		}
		else if (this->mPrefabRes->hasFailed())
		{
			this->mResLoadState->setFailed();

			GObjectAssetInsMg->unload(this->mPrefabRes->getResUniqueId(), AuxPrefabLoader::onPrefabLoaded);
			this->mPrefabRes = nullptr;

			if (this->mEvtHandle != nullptr)
			{
				this->mEvtHandle->dispatchEvent(this);
			}
		}
	}
	else
	{
		if (this->mEvtHandle != nullptr)
		{
			this->mEvtHandle->dispatchEvent(this);
		}
	}
}

void AuxPrefabLoader::onPrefabIns(IDispatchObject* dispObj)
{
	this->mResInsEventDispatch = (ResInsEventDispatch*)dispObj;
	this->setSelfGo(this->mResInsEventDispatch->getInsGO());
	this->onAllFinish();
}

// 所有的资源都加载完成
void AuxPrefabLoader::onAllFinish()
{
	if (this->mIsNeedInsPrefab)
	{
		if (this->selfGo != nullptr)
		{
			this->mResLoadState->setSuccessLoaded();
		}
		else
		{
			this->mResLoadState->setFailed();
		}
	}
	else
	{
		if (nullptr != this->mPrefabRes && this->mPrefabRes->hasSuccessLoaded())
		{
			this->mResLoadState->setSuccessLoaded();
		}
		else
		{
			this->mResLoadState->setFailed();
		}
	}

	if (this->mEvtHandle != nullptr)
	{
		this->mEvtHandle->dispatchEvent(this);
	}
}

void AuxPrefabLoader::unload()
{
	if (this->mPrefabRes != nullptr)
	{
		GObjectAssetInsMgr->unload(this->mPrefabRes->getResUniqueId(), AuxPrefabLoader::onPrefabLoaded);
		this->mPrefabRes = nullptr;
	}

	if (this->mResInsEventDispatch != nullptr)
	{
		this->mResInsEventDispatch->setIsValid(false);
		this->mResInsEventDispatch = nullptr;
	}

	if (this->mEvtHandle != nullptr)
	{
		this->mEvtHandle.clearEventHandle();
		this->mEvtHandle = nullptr;
	}
}

UObject* AuxPrefabLoader::getGameObject()
{
	return this->mSelfGo;
}

// 获取预制模板
UObject* AuxPrefabLoader::getPrefabTmpl()
{
	UObject* ret = nullptr;
	if (nullptr != this->mPrefabRes)
	{
		ret = this->mPrefabRes->getObject();
	}
	return ret;
}

void AuxPrefabLoader::setClientDispose(bool isDispose)
{

}

bool AuxPrefabLoader::isClientDispose()
{
	return false;
}

UObject* AuxPrefabLoader::InstantiateObject(EventDispatchDelegate insHandle)
{
	if (nullptr == this->mInsEventDispatch && nullptr != insHandle)
	{
		this->mInsEventDispatch = new ResInsEventDispatch();
	}
	if (nullptr != insHandle)
	{
		this->mInsEventDispatch->addEventHandle(nullptr, insHandle);
	}

	if (this->mIsInsNeedCoroutine)
	{
		if (nullptr == this->mResInsEventDispatch)
		{
			this->mResInsEventDispatch = new ResInsEventDispatch();
		}
		this->mResInsEventDispatch->addEventHandle(nullptr, AuxPrefabLoader::onInstantiateObjectFinish);

		if (this->mIsSetFakePos)
		{
			this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilApi.FAKE_POS, UtilMath.UnitQuat, this->mResInsEventDispatch);
		}
		else
		{
			this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilMath.ZeroVec3, UtilMath.UnitQuat, this->mResInsEventDispatch);
		}
	}
	else
	{
		if (this->mIsSetFakePos)
		{
			this->setSelfGo(this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilApi.FAKE_POS, UtilMath.UnitQuat));
		}
		else
		{
			this->setSelfGo(this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilMath.ZeroVec3, UtilMath.UnitQuat));
		}

		this->onInstantiateObjectFinish();
	}

	return this->mSelfGo;
}

void AuxPrefabLoader::onInstantiateObjectFinish(IDispatchObject* dispObj)
{
	if (nullptr != dispObj)
	{
		this->setSelfGo(this->mResInsEventDispatch->getInsGO());
	}

	if (nullptr != this->mInsEventDispatch)
	{
		this->mInsEventDispatch->dispatchEvent(this);
	}
}