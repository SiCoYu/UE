#include "MyProject.h"
#include "AuxMObjectLoaderBase.h"
#include "UtilMath.h"
#include "UtilSysLibWrap.h"
#include "ObjectAssetInsRes.h"
#include "Prequisites.h"
#include "ResInsEventDispatch.h"
#include "ResLoadState.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxMObjectLoaderBase, AuxLoaderBase)

AuxMObjectLoaderBase::AuxMObjectLoaderBase(std::string path, bool isNeedInsPrefab, bool isInsNeedCoroutine)
	: Super(path)
{
	this->mIsInsNeedCoroutine = isInsNeedCoroutine;
	this->mIsDestroySelf = true;
	this->mIsNeedInsPrefab = isNeedInsPrefab;

	this->mIsSetInitOrientPos = false;
	this->mIsSetFakePos = false;

	this->mResInsEventDispatch = nullptr;
	this->mSelfActor = nullptr;
	this->mPrefabRes = nullptr;
	this->mInsEventDispatch = nullptr;
}

void AuxMObjectLoaderBase::setIsInitOrientPos(bool isSet)
{
	this->mIsSetInitOrientPos = isSet;
}

void AuxMObjectLoaderBase::setIsFakePos(bool isSet)
{
	this->mIsSetFakePos = isSet;
}

void AuxMObjectLoaderBase::dispose()
{
	if (this->mIsDestroySelf)
	{
		if (this->mSelfActor != nullptr)
		{
			UtilSysLibWrap::DestroyImmediate(Cast<AActor>(this->mSelfActor));
		}
	}

	Super::dispose();
}

UObject* AuxMObjectLoaderBase::getSelfActor()
{
	return this->mSelfActor;
}

void AuxMObjectLoaderBase::setSelfActor(UObject* value)
{
	this->mSelfActor = value;
}

bool AuxMObjectLoaderBase::isDestroySelf()
{
	return this->mIsDestroySelf;
}

void AuxMObjectLoaderBase::setDestroySelf(bool value)
{
	this->mIsDestroySelf = value;
}

std::string AuxMObjectLoaderBase::getOrigPath()
{
	if (this->mPrefabRes != nullptr)
	{
		return this->mPrefabRes->getOrigPath();
	}

	return this->mPath;
}

void AuxMObjectLoaderBase::syncLoad(
	std::string path, 
	EventDispatchDelegate evtHandle,
	EventDispatchDelegate progressHandle
)
{
	Super::syncLoad(path, evtHandle);

	if (this->isInvalid())
	{
		if (ResPackType::eClassType == this->mResPackType)
		{
			this->mPrefabRes = GClassAssetInsMgr->getAndSyncLoadRes(path, evtHandle);
		}
		else if (ResPackType::eObjectType == this->mResPackType)
		{
			this->mPrefabRes = GObjectAssetInsMgr->getAndSyncLoadRes(path, evtHandle);
		}
		this->onPrefabLoaded(mPrefabRes);
	}
	else if (this->hasLoadEnd())
	{
		this->onPrefabLoaded(mPrefabRes);
	}
}

// 异步加载对象
void AuxMObjectLoaderBase::asyncLoad(
	std::string path, 
	EventDispatchDelegate evtHandle,
	EventDispatchDelegate progressHandle)
{
	Super::asyncLoad(path, evtHandle);

	if (this->isInvalid())
	{
		if (ResPackType::eClassType == this->mResPackType)
		{
			this->mPrefabRes = GClassAssetInsMgr->getAndAsyncLoadRes(
				path, 
				MakeEventDispatchDelegate(
					this, 
					&AuxMObjectLoaderBase::onPrefabLoaded
				)
			);
		}
		else if (ResPackType::eObjectType == this->mResPackType)
		{
			this->mPrefabRes = GObjectAssetInsMgr->getAndAsyncLoadRes(
				path, 
				MakeEventDispatchDelegate(
					this, 
					&AuxMObjectLoaderBase::onPrefabLoaded
				)
			);
		}
	}
	else if (this->hasLoadEnd())
	{
		this->onPrefabLoaded(this->mPrefabRes);
	}
}

void AuxMObjectLoaderBase::onPrefabLoaded(IDispatchObject* dispObj)
{
	if (nullptr != dispObj)
	{
		// 一定要从这里再次取值，因为如果这个资源已经加载，可能在返回之前就先调用这个函数，因此这个时候 mPrefabRes 还是空值
		this->mPrefabRes = (ObjectAssetInsRes*)dispObj;

		if (this->mPrefabRes->hasSuccessLoaded())
		{
			this->mResLoadState->setSuccessLoaded();

			if (this->mIsNeedInsPrefab)
			{
				if (this->mIsInsNeedCoroutine)
				{
					this->mResInsEventDispatch = MY_NEW ResInsEventDispatch();
					this->mResInsEventDispatch->addEventHandle(
						MakeEventDispatchDelegate(
							this, 
							&AuxMObjectLoaderBase::onPrefabIns
						)
					);

					if (this->mIsSetFakePos)
					{
						this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilSysLibWrap::FAKE_POS, UtilMath::UnitQuat, this->mResInsEventDispatch);
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
						this->setSelfActor(this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilSysLibWrap::FAKE_POS, UtilMath::UnitQuat));
					}
					else
					{
						this->setSelfActor(this->mPrefabRes->InstantiateObject(this->mPrefabRes->getPrefabName(), this->mIsSetInitOrientPos, UtilMath::ZeroVec3, UtilMath::UnitQuat));
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

			GObjectAssetInsMgr->unload(
				this->mPrefabRes->getResUniqueId(), 
				MakeEventDispatchDelegate(
					this, 
					&AuxMObjectLoaderBase::onPrefabLoaded
				)
			);
			this->mPrefabRes = nullptr;

			if (this->mResEventDispatch != nullptr)
			{
				this->mResEventDispatch->dispatchEvent(this);
			}
		}
	}
	else
	{
		if (this->mResEventDispatch != nullptr)
		{
			this->mResEventDispatch->dispatchEvent(this);
		}
	}
}

void AuxMObjectLoaderBase::onPrefabIns(IDispatchObject* dispObj)
{
	this->mResInsEventDispatch = (ResInsEventDispatch*)dispObj;
	this->setSelfActor(this->mResInsEventDispatch->getInsActor());
	this->onAllFinish();
}

// 所有的资源都加载完成
void AuxMObjectLoaderBase::onAllFinish()
{
	if (this->mIsNeedInsPrefab)
	{
		if (this->mSelfActor != nullptr)
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

	if (this->mResEventDispatch != nullptr)
	{
		this->mResEventDispatch->dispatchEvent(this);
	}
}

void AuxMObjectLoaderBase::unload()
{
	if (this->mPrefabRes != nullptr)
	{
		GObjectAssetInsMgr->unload(
			this->mPrefabRes->getResUniqueId(), 
			MakeEventDispatchDelegate(
				this, 
				&AuxMObjectLoaderBase::onPrefabLoaded
			)
		);

		this->mPrefabRes = nullptr;
	}

	if (this->mResInsEventDispatch != nullptr)
	{
		this->mResInsEventDispatch->setIsValid(false);
		MY_SAFE_DISPOSE(this->mResInsEventDispatch);
	}

	if (this->mResEventDispatch != nullptr)
	{
		this->mResEventDispatch->clearEventHandle();
		MY_SAFE_DISPOSE(this->mResEventDispatch);
	}

	Super::unload();
}

UObject* AuxMObjectLoaderBase::getActor()
{
	return this->mSelfActor;
}

// 获取预制模板
UObject* AuxMObjectLoaderBase::getPrefabTmpl()
{
	UObject* ret = nullptr;
	if (nullptr != this->mPrefabRes)
	{
		ret = Cast<UObject>(this->mPrefabRes->getObject());
	}
	return ret;
}

UObject* AuxMObjectLoaderBase::InstantiateObject(EventDispatchDelegate insHandle)
{
	if (nullptr == this->mInsEventDispatch && nullptr != insHandle)
	{
		this->mInsEventDispatch = MY_NEW ResInsEventDispatch();
	}
	if (nullptr != insHandle)
	{
		this->mInsEventDispatch->addEventHandle(insHandle);
	}

	if (this->mIsInsNeedCoroutine)
	{
		if (nullptr == this->mResInsEventDispatch)
		{
			this->mResInsEventDispatch = MY_NEW ResInsEventDispatch();
		}
		this->mResInsEventDispatch->addEventHandle(
			MakeEventDispatchDelegate(
				this,
				&AuxMObjectLoaderBase::onInstantiateObjectFinish
			)
		);

		if (this->mIsSetFakePos)
		{
			this->mPrefabRes->InstantiateObject(
				this->mPrefabRes->getPrefabName(), 
				this->mIsSetInitOrientPos, 
				UtilSysLibWrap::FAKE_POS, 
				UtilMath::UnitQuat, 
				this->mResInsEventDispatch
			);
		}
		else
		{
			this->mPrefabRes->InstantiateObject(
				this->mPrefabRes->getPrefabName(), 
				this->mIsSetInitOrientPos, 
				UtilMath::ZeroVec3, 
				UtilMath::UnitQuat, 
				this->mResInsEventDispatch
			);
		}
	}
	else
	{
		if (this->mIsSetFakePos)
		{
			this->setSelfActor(
				this->mPrefabRes->InstantiateObject(
					this->mPrefabRes->getPrefabName(), 
					this->mIsSetInitOrientPos, 
					UtilSysLibWrap::FAKE_POS, 
					UtilMath::UnitQuat
				)
			);
		}
		else
		{
			this->setSelfActor(
				this->mPrefabRes->InstantiateObject(
					this->mPrefabRes->getPrefabName(), 
					this->mIsSetInitOrientPos, 
					UtilMath::ZeroVec3, 
					UtilMath::UnitQuat
				)
			);
		}

		this->onInstantiateObjectFinish();
	}

	return this->mSelfActor;
}

void AuxMObjectLoaderBase::onInstantiateObjectFinish(IDispatchObject* dispObj)
{
	if (nullptr != dispObj)
	{
		this->setSelfActor(this->mResInsEventDispatch->getInsActor());
	}

	if (nullptr != this->mInsEventDispatch)
	{
		this->mInsEventDispatch->dispatchEvent(this);
	}
}

MY_END_NAMESPACE