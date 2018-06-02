#include "MyProject.h"
#include "AuxDownloader.h"
#include "DownloadItem.h"
#include "Prequisites.h"

MY_BEGIN_NAMESPACE(MyNS)

char* AuxDownloader::getBytes()
{
	if (this->mDownloadItem != nullptr)
	{
		return this->mDownloadItem->getBytes();
	}

	return nullptr;
}

// 下载一个资源
void AuxDownloader::download(
	std::string origPath, 
	EventDispatchDelegate dispObj, 
	long fileLen, 
	bool isWriteFile, 
	int downloadType
)
{
	Super::download(
		origPath, 
		dispObj, 
		fileLen, 
		isWriteFile, 
		downloadType
	);

	if (this->isInvalid())
	{
		DownloadParam* param = MY_NEW DownloadParam();

		param->setPath(origPath);
		param->mLoadEventHandle = MakeEventDispatchDelegate(
			this, 
			&AuxDownloader::onDownloaded
		);
		param->mFileLen = fileLen;
		param->mIsWriteFile = isWriteFile;
		param->mDownloadType = (DownloadType)downloadType;

		GDownloadMgr->download(param);
	}
	else if (this->hasLoadEnd())
	{
		this->onDownloaded(this->mDownloadItem);
	}
}

// 下载完成
void AuxDownloader::onDownloaded(IDispatchObject* dispObj)
{
	if (nullptr != dispObj)
	{
		this->mDownloadItem = (DownloadItem*)dispObj;

		if (this->mDownloadItem->hasSuccessLoaded())
		{
			this->mResLoadState->setSuccessLoaded();
		}
		else if (this->mDownloadItem->hasFailed())
		{
			this->mResLoadState->setFailed();
			this->mDownloadItem = nullptr;
		}
	}

	if (this->mResEventDispatch != nullptr)
	{
		this->mResEventDispatch->dispatchEvent(this);
	}
}

MY_END_NAMESPACE