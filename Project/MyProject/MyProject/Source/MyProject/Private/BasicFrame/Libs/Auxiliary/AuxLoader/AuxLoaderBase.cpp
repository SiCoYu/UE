#include "MyProject.h"
#include "AuxLoaderBase.h"
#include "ResLoadState.h"
#include "ResLoadStateCV.h"
#include "ResEventDispatch.h"
#include "MClassFactory.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(AuxLoaderBase, GObject)

AuxLoaderBase::AuxLoaderBase()
{
	this->mResEventDispatch = nullptr;
	this->mInitPath = "";
	this->mResLoadState = MY_NEW ResLoadState();
	this->mResLoadPriority = ResLoadPriority::eRLP_Low_1000;

	this->mResEventDispatch = nullptr;
	this->mProgressEventDispatch = nullptr;

	this->reset();
}

void AuxLoaderBase::reset()
{
	this->mResLoadState->reset();
	this->mPrePath = "";
	this->mPath = "";
	this->mIsInvalid = true;
}

void AuxLoaderBase::init()
{
	this->mResLoadState->init();
}

void AuxLoaderBase::dispose()
{
	MY_SAFE_DISPOSE(this->mResLoadState);
	MY_SAFE_DISPOSE(this->mResEventDispatch);
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
	this->mPrePath = this->mPath;
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

std::string AuxLoaderBase::getOrigPath()
{
	return this->mPath;
}

// 真正的开始加载
void AuxLoaderBase::onStartLoad()
{
	this->mResLoadState->setLoading();
}

// 资源加载完成成功
void AuxLoaderBase::onLoaded()
{
	this->mResLoadState->setSuccessLoaded();
}

// 加载失败
void AuxLoaderBase::onFailed()
{
	this->mResLoadState->setFailed();
}

// 开始实例化
void AuxLoaderBase::onStartIns()
{
	this->mResLoadState->setInsing();
}

// 实例化完成成功
void AuxLoaderBase::onSuccessIns()
{
	this->mResLoadState->setSuccessIns();
}

// 实例化失败
void AuxLoaderBase::onInsFailed()
{
	this->mResLoadState->setInsFailed();
}

void AuxLoaderBase::addEventHandle(EventDispatchDelegate evtHandle)
{
	if (nullptr == this->mResEventDispatch)
	{
		this->mResEventDispatch = MY_NEW ResEventDispatch();
	}

	this->mResEventDispatch->addEventHandle(evtHandle);
}

void AuxLoaderBase::syncLoad(
	std::string path, 
	EventDispatchDelegate evtHandle,
	EventDispatchDelegate progressHandle
)
{
	this->mResLoadState->setLoading();

	this->updatePath(path);

	this->addEventHandle(evtHandle);
}

void AuxLoaderBase::asyncLoad(
	std::string path, 
	EventDispatchDelegate evtHandle,
	EventDispatchDelegate progressHandle)
{
	this->mResLoadState->setLoading();

	this->updatePath(path);

	this->addEventHandle(evtHandle);
}

void AuxLoaderBase::download(
	std::string origPath, 
	EventDispatchDelegate handle, 
	long fileLen, 
	bool isWriteFile, 
	int downloadType
)
{
	this->mResLoadState->setLoading();

	this->updatePath(origPath);

	this->addEventHandle(handle);
}

void AuxLoaderBase::unload()
{
	if (this->mResEventDispatch != nullptr)
	{
		this->mResEventDispatch->clearEventHandle();
		MY_SAFE_DISPOSE(this->mResEventDispatch);
	}

	if (this->mProgressEventDispatch != nullptr)
	{
		this->mProgressEventDispatch->clearEventHandle();
		MY_SAFE_DISPOSE(this->mProgressEventDispatch);
	}

	this->reset();
}

void AuxLoaderBase::onProgressEventHandle(IDispatchObject* dispObj)
{
	if (nullptr != this->mProgressEventDispatch)
	{
		this->mProgressEventDispatch->dispatchEvent(dispObj);
	}
}

MY_END_NAMESPACE