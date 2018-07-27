#include "MyProject.h"
#include "AuxMaterialLoader.h"
#include "Materials/MaterialInstanceDynamic.h"	// UMaterialInstanceDynamic
#include "MaterialInsRes.h"
#include "Prequisites.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxMaterialLoader, AuxLoaderBase)

AuxMaterialLoader::AuxMaterialLoader()
	: Super()
{
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

std::string& AuxMaterialLoader::getOrigPath()
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
			EventDispatchDelegate(),
			EventDispatchDelegate(),
            this->mResLoadPriority
        );

        this->onMaterialLoaded((uint)0, this->mMaterialRes);
    }
    else if (this->hasLoadEnd())
    {
        //this->onMaterialLoaded(this->mMaterialRes);
        this->onMaterialLoaded((uint)0, nullptr);
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

        if (progressHandle.empty())
        {
            this->mMaterialRes = GMaterialInsResMgr->getAndAsyncLoadRes(
                path,
				MakeEventDispatchDelegate(
					this,
					&AuxMaterialLoader::onMaterialLoaded, 
					(uint)0
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
					(uint)0
				), 
				MakeEventDispatchDelegate(
					this,
					&AuxLoaderBase::onProgressEventHandle, 
					(uint)0
				)
            );
        }
    }
    else if (this->hasLoadEnd())
    {
        this->onMaterialLoaded((uint)0, nullptr);
    }
}

void AuxMaterialLoader::onMaterialLoaded(uint eventId, IDispatchObject* dispObj)
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
					(uint)0
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
				(uint)0
			)
        );

        this->mMaterialRes = nullptr;
    }

	Super::unload();
}

MY_END_NAMESPACE