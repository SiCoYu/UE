#include "MyProject.h"
#include "AuxMObjectLoader.h"
#include "UtilMath.h"
#include "UtilApi.h"
#include "ObjectAssetResItem.h"
#include "Common.h"

namespace MyNS
{
	AuxMObjectLoader::AuxMObjectLoader(std::string path, bool isNeedInsPrefab, bool isInsNeedCoroutine)
		: Super(path)
	{
		this->mIsInsNeedCoroutine = isInsNeedCoroutine;
		this->mIsDestroySelf = true;
		this->mIsNeedInsPrefab = isNeedInsPrefab;

		this->mIsSetInitOrientPos = false;
		this->mIsSetFakePos = false;
	}

	void AuxMObjectLoader::setIsInitOrientPos(bool isSet)
	{
		this->mIsSetInitOrientPos = isSet;
	}

	void AuxMObjectLoader::setIsFakePos(bool isSet)
	{
		this->mIsSetFakePos = isSet;
	}

	void AuxMObjectLoader::dispose()
	{
		if (this->mIsDestroySelf)
		{
			if (this->mSelfGo != nullptr)
			{
				//UtilApi.DestroyImmediate(this.mSelfGo);
			}
		}

		Super::dispose();
	}

	UObject* AuxMObjectLoader::getSelfGo()
	{
		return this->mSelfGo;
	}

	void AuxMObjectLoader::setSelfGo(UObject* value)
	{
		this->mSelfGo = value;
	}

	bool AuxMObjectLoader::isDestroySelf()
	{
		return this->mIsDestroySelf;
	}

	void AuxMObjectLoader::setDestroySelf(bool value)
	{
		this->mIsDestroySelf = value;
	}

	std::string AuxMObjectLoader::getLogicPath()
	{
		if (this->mPrefabRes != nullptr)
		{
			return this->mPrefabRes->getLogicPath();
		}

		return this->mPath;
	}

	void AuxMObjectLoader::syncLoad(std::string path, EventDispatchDelegate evtHandle)
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
	void AuxMObjectLoader::asyncLoad(std::string path, EventDispatchDelegate evtHandle)
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

	void AuxMObjectLoader::onPrefabLoaded(IDispatchObject* dispObj)
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
							this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilApi::FAKE_POS, UtilMath::UnitQuat, this->mResInsEventDispatch);
						}
						else
						{
							this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilMath::ZeroVec3, UtilMath::UnitQuat, this->mResInsEventDispatch);
						}
					}
					else
					{
						if (this->mIsSetFakePos)
						{
							this->setSelfGo(this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilApi::FAKE_POS, UtilMath::UnitQuat));
						}
						else
						{
							this->setSelfGo(this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilMath::ZeroVec3, UtilMath::UnitQuat));
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

	void AuxMObjectLoader::onPrefabIns(IDispatchObject* dispObj)
	{
		this->mResInsEventDispatch = (ResInsEventDispatch*)dispObj;
		this->setSelfGo(this->mResInsEventDispatch->getInsGO());
		this->onAllFinish();
	}

	// 所有的资源都加载完成
	void AuxMObjectLoader::onAllFinish()
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

	void AuxMObjectLoader::unload()
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

	UObject* AuxMObjectLoader::getGameObject()
	{
		return this->mSelfGo;
	}

	// 获取预制模板
	UObject* AuxMObjectLoader::getPrefabTmpl()
	{
		UObject* ret = nullptr;
		if (nullptr != this->mPrefabRes)
		{
			ret = this->mPrefabRes->getObject();
		}
		return ret;
	}

	void AuxMObjectLoader::setClientDispose(bool isDispose)
	{

	}

	bool AuxMObjectLoader::isClientDispose()
	{
		return false;
	}

	UObject* AuxMObjectLoader::InstantiateObject(EventDispatchDelegate insHandle)
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
				this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilApi::FAKE_POS, UtilMath::UnitQuat, this->mResInsEventDispatch);
			}
			else
			{
				this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilMath::ZeroVec3, UtilMath::UnitQuat, this->mResInsEventDispatch);
			}
		}
		else
		{
			if (this->mIsSetFakePos)
			{
				this->setSelfGo(this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilApi::FAKE_POS, UtilMath::UnitQuat));
			}
			else
			{
				this->setSelfGo(this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilMath::ZeroVec3, UtilMath::UnitQuat));
			}

			this->onInstantiateObjectFinish();
		}

		return this->mSelfGo;
	}

	void AuxMObjectLoader::onInstantiateObjectFinish(IDispatchObject* dispObj)
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
}