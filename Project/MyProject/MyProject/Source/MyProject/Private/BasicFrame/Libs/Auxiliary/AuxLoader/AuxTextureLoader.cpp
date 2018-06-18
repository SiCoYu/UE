#include "MyProject.h"
#include "AuxTextureLoader.h"
#include "Engine/Texture.h"	// UTexture
#include "TextureInsRes.h"
#include "Prequisites.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxTextureLoader, AuxLoaderBase)

AuxTextureLoader::AuxTextureLoader()
	: Super()
{
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
			EventDispatchDelegate(),
			EventDispatchDelegate(),
            this->mResLoadPriority
            );
        this->onTextureLoaded((uint)0, this->mTextureRes);
    }
    else if (this->hasLoadEnd())
    {
        //this->onTextureLoaded(this->mTextureRes);
        this->onTextureLoaded((uint)0, nullptr);
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

        if (progressHandle.empty())
        {
            this->mTextureRes = GTextureInsResMgr->getAndAsyncLoadRes(
                path,
				MakeEventDispatchDelegate(
					this,
					&AuxTextureLoader::onTextureLoaded, 
					(uint)0
				)
            );
        }
        else
        {
            this->mTextureRes = GTextureInsResMgr->getAndAsyncLoadRes(
                path,
				MakeEventDispatchDelegate(
					this,
					&AuxTextureLoader::onTextureLoaded, 
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
        this->onTextureLoaded((uint)0, nullptr);
    }
}

void AuxTextureLoader::onTextureLoaded(uint eventId, IDispatchObject* dispObj)
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
				MakeEventDispatchDelegate(
					this,
					&AuxTextureLoader::onTextureLoaded, 
					(uint)0
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
			MakeEventDispatchDelegate(
				this,
				&AuxTextureLoader::onTextureLoaded, 
				(uint)0
			)
        );

        this->mTextureRes = nullptr;
    }

	Super::unload();
}

MY_END_NAMESPACE