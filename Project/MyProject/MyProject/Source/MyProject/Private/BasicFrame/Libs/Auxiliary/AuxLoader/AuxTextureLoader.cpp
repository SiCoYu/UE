#include "MyProject.h"
#include "AuxTextureLoader.h"
#include "Engine/Texture.h"	// UTexture
#include "TextureInsRes.h"
#include "Prequisites.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxTextureLoader, AuxLoaderBase)

AuxTextureLoader::AuxTextureLoader()
{
	Super();

    this->mTextureRes = nullptr;
    this->mTexture = nullptr;
}

void AuxTextureLoader::dispose()
{
	Super::dispose();
}

UTexture* AuxTextureLoader::getTexture()
{
    return this->mTexture;
}

std::string AuxTextureLoader::getOrigPath()
{
    if (this->mTextureRes != nullptr)
    {
        return this->mTextureRes->getOrigPath();
    }

    return this->mPath;
}

void AuxTextureLoader::syncLoad(
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

        this->mTextureRes = GTextureInsResMgr->getAndSyncLoadRes(
            path, 
			nullptr,
			nullptr,
            this->mResLoadPriority
            );
        this->onTextureLoaded(this->mTextureRes);
    }
    else if (this->hasLoadEnd())
    {
        //this->onTextureLoaded(this->mTextureRes);
        this->onTextureLoaded(nullptr);
    }
}

// 异步加载对象
void AuxTextureLoader::asyncLoad(
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
            this->mTextureRes = GTextureInsResMgr->getAndAsyncLoadRes(
                path,
				EventDispatchDelegate(
					this,
					&AuxTextureLoader::onTextureLoaded
				)
            );
        }
        else
        {
            this->mTextureRes = GTextureInsResMgr->getAndAsyncLoadRes(
                path,
				EventDispatchDelegate(
					this,
					&AuxTextureLoader::onTextureLoaded
				),
				EventDispatchDelegate(
					this,
					&AuxLoaderBase::onProgressEventHandle
				)
            );
        }
    }
    else if (this->hasLoadEnd())
    {
        this->onTextureLoaded(nullptr);
    }
}

void AuxTextureLoader::onTextureLoaded(IDispatchObject* dispObj)
{
    if (nullptr != dispObj)
    {
        this->mTextureRes = (TextureInsRes*)dispObj;

        if (this->mTextureRes->hasSuccessLoaded())
        {
            this->onLoaded();

            this->mTexture = this->mTextureRes->getTexture();
        }
        else if (this->mTextureRes->hasFailed())
        {
            this->onFailed();

			GTextureInsResMgr->unload(
                this->mTextureRes->getResUniqueId(),
				EventDispatchDelegate(
					this,
					&AuxTextureLoader::onTextureLoaded
					)
				);
            this->mTextureRes = nullptr;
        }
    }

    if (nullptr != this->mResEventDispatch)
    {
        this->mResEventDispatch->dispatchEvent(this);
    }
}

void AuxTextureLoader::unload()
{
    if(nullptr != this->mTextureRes)
    {
		GTextureInsResMgr->unload(
            this->mTextureRes->getResUniqueId(),
			EventDispatchDelegate(
				this,
				&AuxTextureLoader::onTextureLoaded
				)
            );
        this->mTextureRes = nullptr;
    }

	Super::unload();
}

MY_END_NAMESPACE