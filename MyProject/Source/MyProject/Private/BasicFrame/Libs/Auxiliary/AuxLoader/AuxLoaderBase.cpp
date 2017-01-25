#include "MyProject.h"
#include "AuxLoaderBase.h"
#include "ResLoadState.h"
#include "ResEventDispatch.h"

namespace MyNS
{
	AuxLoaderBase::AuxLoaderBase(std::string path)
	{
		this->mInitPath = path;
		this->mResLoadState = new ResLoadState();

		this->reset();
	}

	void AuxLoaderBase::reset()
	{
		this->mResLoadState->reset();
		this->mPrePath = "";
		this->mPath = "";
		this->mIsInvalid = true;
	}

	void AuxLoaderBase::dispose()
	{
		this->unload();
	}

	bool AuxLoaderBase::hasSuccessLoaded()
	{
		return this->mResLoadState->hasSuccessLoaded();
	}

	bool AuxLoaderBase::hasFailed()
	{
		return this->mResLoadState->hasFailed();
	}

	// 加载成功或者加载失败
	bool AuxLoaderBase::hasLoadEnd()
	{
		return (this->hasSuccessLoaded() || this->hasFailed());
	}

	// 是否需要卸载资源
	bool AuxLoaderBase::needUnload(std::string path)
	{
		return this->mPath != path && !UtilStr::IsNullOrEmpty(path) && !UtilStr::IsNullOrEmpty(this->mPath);
	}

	void AuxLoaderBase::setPath(std::string path)
	{
		this->mPrePath = mPath;
		this->mPath = path;

		if (this->mPrePath != this->mPath && !UtilStr::IsNullOrEmpty(this->mPath))
		{
			this->mIsInvalid = true;
		}
		else
		{
			this->mIsInvalid = false;
		}
	}

	void AuxLoaderBase::updatePath(std::string path)
	{
		if (this->needUnload(path))
		{
			this->unload();
		}

		this->setPath(path);
	}

	bool AuxLoaderBase::isInvalid()
	{
		return this->mIsInvalid;
	}

	std::string AuxLoaderBase::getLogicPath()
	{
		return this->mPath;
	}

	void AuxLoaderBase::addEventHandle(EventDispatchDelegate evtHandle)
	{
		if (nullptr != evtHandle)
		{
			if (nullptr == this->mEvtHandle)
			{
				this->mEvtHandle = new ResEventDispatch();
			}
			this->mEvtHandle->addEventHandle(evtHandle);
		}
	}

	void AuxLoaderBase::syncLoad(std::string path, EventDispatchDelegate evtHandle)
	{
		this->mResLoadState->setLoading();

		this->updatePath(path);

		this->addEventHandle(evtHandle);
	}

	void AuxLoaderBase::asyncLoad(std::string path, EventDispatchDelegate evtHandle)
	{
		this->mResLoadState->setLoading();

		this->updatePath(path);

		this->addEventHandle(evtHandle);
	}

	void AuxLoaderBase::download(std::string origPath, EventDispatchDelegate  dispObj, long fileLen, bool isWriteFile, int downloadType)
	{
		this->mResLoadState->setLoading();

		this->updatePath(origPath);

		this->addEventHandle(dispObj);
	}

	void AuxLoaderBase::unload()
	{
		if (this->mEvtHandle != nullptr)
		{
			this->mEvtHandle->clearEventHandle();
			this->mEvtHandle = nullptr;
		}

		this->reset();
	}
}