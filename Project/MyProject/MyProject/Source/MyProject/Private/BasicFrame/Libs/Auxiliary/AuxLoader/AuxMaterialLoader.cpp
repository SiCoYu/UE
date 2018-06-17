#include "MyProject.h"
#include "AuxMaterialLoader.h"
#include "Materials/MaterialInstanceDynamic.h"	// UMaterialInstanceDynamic
#include "MaterialInsRes.h"
#include "Prequisites.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxMaterialLoader, AuxLoaderBase)

AuxMaterialLoader::AuxMaterialLoader()
{
	Super();

    this->mMaterialRes = nullptr;
    this->mMaterial = nullptr;
}

void AuxMaterialLoader::dispose()
{
	Super::dispose();
}

UMaterialInterface* AuxMaterialLoader::getMaterialInterface()
{
	return this->mMaterialDyn;
}

UMaterialInstanceDynamic* AuxMaterialLoader::getMaterialInterfaceDynamic()
{
	return this->mMaterialDyn;
}

std::string AuxMaterialLoader::getOrigPath()
{
    if (this->mMaterialRes != nullptr)
    {
        return this->mMaterialRes->getOrigPath();
    }

    return this->mPath;
}

void AuxMaterialLoader::syncLoad(
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
        this->onStartLoad();

        this->mMaterialRes = GMaterialInsResMgr->getAndSyncLoadRes(
            path, 
			nullptr,
			nullptr,
            this->mResLoadPriority
            );
        this->onMaterialLoaded(this->mMaterialRes);
    }
    else if (this->hasLoadEnd())
    {
        //this->onMaterialLoaded(this->mMaterialRes);
        this->onMaterialLoaded(nullptr);
    }
}

// 异步加载对象
void AuxMaterialLoader::asyncLoad(
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
        this->onStartLoad();

        if (nullptr == progressHandle)
        {
            this->mMaterialRes = GMaterialInsResMgr->getAndAsyncLoadRes(
                path,
				MakeEventDispatchDelegate(
					this,
					&AuxMaterialLoader::onMaterialLoaded, 
					0
				)
            );
        }
        else
        {
            this->mMaterialRes = GMaterialInsResMgr->getAndAsyncLoadRes(
                path,
				MakeEventDispatchDelegate(
					this,
					&AuxMaterialLoader::onMaterialLoaded, 
					0
				),
				MakeEventDispatchDelegate(
					this,
					&AuxLoaderBase::onProgressEventHandle, 
					0
				)
            );
        }
    }
    else if (this->hasLoadEnd())
    {
        this->onMaterialLoaded(nullptr);
    }
}

void AuxMaterialLoader::onMaterialLoaded(IDispatchObject* dispObj, uint eventId)
{
    if (nullptr != dispObj)
    {
        this->mMaterialRes = (MaterialInsRes*)dispObj;

        if (this->mMaterialRes->hasSuccessLoaded())
        {
            this->onLoaded();

            this->mMaterial = this->mMaterialRes->getMaterialInterface();
			this->mMaterialDyn = this->mMaterialRes->getMaterialInterfaceDynamic();
        }
        else if (this->mMaterialRes->hasFailed())
        {
            this->onFailed();

			GMaterialInsResMgr->unload(
                this->mMaterialRes->getResUniqueId(),
				MakeEventDispatchDelegate(
					this,
					&AuxMaterialLoader::onMaterialLoaded, 
					0
				)
			);

            this->mMaterialRes = nullptr;
        }
    }

    if (nullptr != this->mResEventDispatch)
    {
        this->mResEventDispatch->dispatchEvent(this);
    }
}

void AuxMaterialLoader::unload()
{
    if(nullptr != this->mMaterialRes)
    {
		GMaterialInsResMgr->unload(
            this->mMaterialRes->getResUniqueId(),
			MakeEventDispatchDelegate(
				this,
				&AuxMaterialLoader::onMaterialLoaded, 
				0
			)
        );

        this->mMaterialRes = nullptr;
    }

	Super::unload();
}

MY_END_NAMESPACE