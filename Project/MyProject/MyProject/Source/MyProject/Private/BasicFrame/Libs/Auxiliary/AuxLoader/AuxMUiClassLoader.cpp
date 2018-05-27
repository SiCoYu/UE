#include "MyProject.h"
#include "AuxMUiClassLoader.h"
#include "ObjectAssetInsResBase.h"
#include "UtilEngineWrap.h"
#include "UMGWidget.h"
#include "Prequisites.h"

namespace MyNS
{
	M_IMPLEMENT_AND_REGISTER_CLASS(AuxMUiClassLoader, AuxMObjectLoaderBase)

	AuxMUiClassLoader::AuxMUiClassLoader(std::string path, bool isNeedInsPrefab, bool isInsNeedCoroutine)
		: Super(path, isNeedInsPrefab, isInsNeedCoroutine)
	{
		this->mResPackType = eClassType;
		this->mWidgetClass = nullptr;
		this->mWidgetObject = nullptr;
	}

	void AuxMUiClassLoader::setUMGOuterType(UMGOuterType value)
	{
		this->mUMGOuterType = value;
	}

	UUMGWidget* AuxMUiClassLoader::getWidgetObject()
	{
		return this->mWidgetObject;
	}

	void AuxMUiClassLoader::insPrefab()
	{
		this->mWidgetClass = this->mPrefabRes->getClass();

		if (NSFormType::eWorld == this->mUMGOuterType)
		{

		}
		else if (NSFormType::ePlayerController == this->mUMGOuterType)
		{
			this->mWidgetObject = UtilEngineWrap::CreateWidget<UUMGWidget>(GEngineData->getMainPlayerController(), this->mWidgetClass);
		}
		else if (NSFormType::eGameInstance == this->mUMGOuterType)
		{

		}

		this->mWidgetObject->AddToViewport();
	}

	void AuxMUiClassLoader::onPrefabLoaded(IDispatchObject* dispObj)
	{
		if (nullptr != dispObj)
		{
			// 一定要从这里再次取值，因为如果这个资源已经加载，可能在返回之前就先调用这个函数，因此这个时候 mPrefabRes 还是空值
			this->mPrefabRes = (ObjectAssetInsResBase*)dispObj;

			if (this->mPrefabRes->hasSuccessLoaded())
			{
				this->mResLoadState->setSuccessLoaded();

				if (this->mIsNeedInsPrefab)
				{
					if (this->mIsInsNeedCoroutine)
					{
						this->insPrefab();

						this->onAllFinish();
					}
					else
					{
						this->insPrefab();

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

				GObjectAssetInsMgr->unload(this->mPrefabRes->getResUniqueId(), MakeEventDispatchDelegate(this, &AuxMObjectLoaderBase::onPrefabLoaded));
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
}