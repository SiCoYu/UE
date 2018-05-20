#include "MyProject.h"
#include "AuxTextureLoader.h"
#include "Engine/Texture.h"	// UTexture
#include "TextureInsRes.h"
#include "Prequisites.h"

namespace MyNS
{
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
                this.mResLoadPriority
                );
            this->onTextureLoaded(this.mTextureRes, 0);
        }
        else if (this->hasLoadEnd())
        {
            //this->onTextureLoaded(this->mTextureRes);
            this->onTextureLoaded(nullptr, 0);
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
				nullptr
                );
            }
            else
            {
                this.mTextureRes = GTextureInsResMgr->getAndAsyncLoadRes(
                    path,
					EventDispatchDelegate(
						this,
						&AuxTextureLoader::onTextureLoaded
					)
					EventDispatchDelegate(
						this,
						&AuxLoaderBase::onProgressEventHandle
					)
                );
            }
        }
        else if (this->hasLoadEnd())
        {
            this->onTextureLoaded(null, 0);
        }
    }

    void AuxTextureLoader::onTextureLoaded(IDispatchObject* dispObj)
    {
        if (nullptr != dispObj)
        {
            this->mTextureRes = (TextureRes*)dispObj;

            if (this->mTextureRes->hasSuccessLoaded())
            {
                this->onLoaded();

                this->mTexture = this->mTextureRes->getTexture();
            }
            else if (this->mTextureRes->hasFailed())
            {
                this.onFailed();

                Ctx.msInstance.mTextureResMgr.unload(
                    this->mTextureRes->getResUniqueId(),
                    nullptr,
                    this->onTextureLoaded
                    );
                this->mTextureRes = null;
            }
        }

        if (nullptr != this->mResEventDispatch)
        {
            this->mResEventDispatch.dispatchEvent(this);
        }
    }

    void AuxTextureLoader::unload()
    {
        if(null != this->mTextureRes)
        {
            Ctx.msInstance.mTextureResMgr.unload(
                this->mTextureRes->getResUniqueId(),
                nullptr,
                this->onTextureLoaded
                );
            this->mTextureRes = null;
        }

		Super::unload();
    }
}