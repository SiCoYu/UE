#include "MyProject.h"
#include "AutoUpdateSys.h"
#include "MyMemoryInc.h"
#include "FileGroup.h"
#include "AddOnceAndCallOnceEventDispatch.h"
#include "AutoUpdateErrorInfo.h"
#include "AutoUpdateErrorCode.h"
#include "VersionInc.h"
#include "LogInc.h"
#include "MacroDef.h"
#include "FileVerInfo.h"
#include "MDictionary.h"
#include "VerFileName.h"
#include "AuxDownloader.h"
#include "UtilStr.h"
#include "ServerVer.h"
#include "UtilEngineWrap.h"
#include "LocalVer.h"
#include "EventDispatchDelegate.h"
#include "VersionInc.h"
#include "MFileSys.h"
#include "DownloadType.h"
#include "UiBaseInc.h"
#include "UtilFileIO.h"

MY_BEGIN_NAMESPACE(MyNS)

AutoUpdateSys::AutoUpdateSys()
{
	this->mFileGroup = MY_NEW FileGroup();
	this->mOnUpdateEndDispatch = MY_NEW AddOnceAndCallOnceEventDispatch();
	this->mAutoUpdateErrorInfo = MY_NEW AutoUpdateErrorInfo();
}

void AutoUpdateSys::init()
{

}

void AutoUpdateSys::dispose()
{

}

FileGroup* AutoUpdateSys::getFileGroup()
{
	return this->mFileGroup;
}

AutoUpdateErrorCode AutoUpdateSys::getAutoUpdateErrorCode()
{
	return this->mAutoUpdateErrorInfo->getErrorCode();
}

void AutoUpdateSys::setAutoUpdateErrorCode(AutoUpdateErrorCode value)
{
	this->mAutoUpdateErrorInfo->setErrorCode(value);
}

AddOnceAndCallOnceEventDispatch* AutoUpdateSys::getUpdateEndDispatch()
{
	return this->mOnUpdateEndDispatch;
}

void AutoUpdateSys::startUpdate()
{
	this->loadWebMiniVersion();
}

// 成功更新
bool AutoUpdateSys::isUpdateSuccess()
{
	//return this->mFileGroup->isUpdateSuccess();
	return this->mAutoUpdateErrorInfo->getErrorCode() == AutoUpdateErrorCode::eErrorNo;
}

// 成功更新，并且重新下载 Version_P.txt，并且成功更新需要更新的资源文件
bool AutoUpdateSys::isUpdateWebVersionPSuccessAndAllUpdateSuccess()
{
	bool ret = false;

	if (this->isUpdateSuccess())
	{
		if (GVersionSys->mIsNeedUpdateVerFile &&
			GVersionSys->mServerVer->mIsVerLoadSuccess)
		{
			ret = true;
		}
	}

	return ret;
}

void AutoUpdateSys::_checkIsNeedUpdateManifest()
{
	std::string platformManifestName = UtilEngineWrap::getManifestName();
	FileVerInfo* serverManifestInfo = nullptr;
	FileVerInfo* localManifestInfo = nullptr;

	if (GVersionSys->mServerVer->mABPath2HashDic.containsKey(platformManifestName))
	{
		serverManifestInfo = GVersionSys->mServerVer->mABPath2HashDic[platformManifestName];
	}
	if (GVersionSys->mLocalVer->mABPath2Ver_P_Dic.containsKey(platformManifestName))
	{
		localManifestInfo = GVersionSys->mLocalVer->mABPath2Ver_P_Dic[platformManifestName];
	}
	else
	{
		if (GVersionSys->mLocalVer->mABPath2Ver_S_Dic.containsKey(platformManifestName))
		{
			localManifestInfo = GVersionSys->mLocalVer->mABPath2Ver_S_Dic[platformManifestName];
		}
	}

	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("AutoUpdateSys::checkIsNeedUpdateManifest, mIsNeedUpdateManifest is false", LogTypeId::eLogAutoUpdate);
	}
}

void AutoUpdateSys::loadWebMiniVersion()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("AutoUpdateSys::loadWebMiniVersion", LogTypeId::eLogAutoUpdate);
	}

	GVersionSys->mMiniLoadResultDispatch->addEventHandle(
		MakeEventDispatchDelegate(
			this, 
			&AutoUpdateSys::onWebMiniVerLoadResult, 
			(uint)0
		)
	);
	GVersionSys->loadWebMiniVerFile();
}

void AutoUpdateSys::onWebMiniVerLoadResult(uint eventId, IDispatchObject* dispObj)
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("AutoUpdateSys::onWebMiniVerLoadResult", LogTypeId::eLogAutoUpdate);
	}

	//UtilMsg::sendHttpEventLog((uint)EventLogId.eEL_3);

	// 如果 Mini 文件没有从服务器下载成功
	if (!GVersionSys->mServerVer->mIsMiniLoadSuccess)
	{
		this->setAutoUpdateErrorCode(AutoUpdateErrorCode::eErrorDownloadWebVersionMiniFailed);
		this->_downloadWebMiniFail();
	}
	else if (GVersionSys->mIsNeedUpdateApp) // 如果需要更新
	{
		this->_downloadApp();
	}
	else if (GVersionSys->mIsNeedUpdateVerFile) // 如果需要更新版本文件
	{
		// 本地文件版本必须要加载
		GVersionSys->mLoadResultDispatch->addEventHandle(
			MakeEventDispatchDelegate(
				this, 
				&AutoUpdateSys::onWebVerLoadResult, 
				(uint)0
			)
		);
		GVersionSys->loadWebVerFile();
	}
	else
	{
		// 没有任何改变，直接进入游戏
		this->onUpdateEnd();          // 更新结束
	}
}

void AutoUpdateSys::onWebVerLoadResult(uint eventId, IDispatchObject* idspObj)
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("AutoUpdateSys::onWebVerLoadResult, start", LogTypeId::eLogAutoUpdate);
	}

	if (GVersionSys->mServerVer->mIsVerLoadSuccess) // 如果需要更新版本文件
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("AutoUpdateSys::onWebVerLoadResult, mIsVerLoadSuccess is true", LogTypeId::eLogAutoUpdate);
		}

		// 开始正式加载文件
		this->_loadAllUpdateFile();
	}
	else
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("AutoUpdateSys::onWebVerLoadResult, mIsVerLoadSuccess is false", LogTypeId::eLogAutoUpdate);
		}

		this->setAutoUpdateErrorCode(AutoUpdateErrorCode::eErrorDownloadWebVersionPFailed);
		this->onUpdateEnd();          // 更新结束
	}
}

// 下载基本的 Web 文件失败
void AutoUpdateSys::_downloadWebMiniFail()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("AutoUpdateSys::downloadWebMiniFail", LogTypeId::eLogAutoUpdate);
	}

	this->onUpdateEnd();
}

// 下载 App 文件
void AutoUpdateSys::_downloadApp()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("AutoUpdateSys::downloadApp", LogTypeId::eLogAutoUpdate);
	}

	GUiMgr->loadAndShow<UForm>(UiFormId::eUiAppDownload);
}

void AutoUpdateSys::_loadAllUpdateFile()
{
	this->mFileGroup->reset();
	this->mFileGroup->setTotalNum(GVersionSys->mServerVer->mABPath2HashDic.count() - this->_getExcludeUpdateFileNum());

	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log(UtilStr::Format("AutoUpdateSys::loadAllUpdateFile, Start, total = {0}", this->mFileGroup->getTotalNum()), LogTypeId::eLogAutoUpdate);
	}

	//this->checkIsNeedUpdateManifest();

	bool isFileInStreaming = false;
	bool isFileInPersistent = false;
	bool isNeedUpdateFile = false;
	FileVerInfo* fileVerInfo = nullptr;

	typename MDictionary<std::string, FileVerInfo*>::Dictionary& dic = GVersionSys->mServerVer->mABPath2HashDic.getData();
	std::string kvKey;
	FileVerInfo* kvValue = nullptr;
	typename ServerVer::Path2HashDicIterator beginIte;
	typename ServerVer::Path2HashDicIterator endIte;

	beginIte = GVersionSys->mServerVer->mABPath2HashDic.begin();
	endIte = GVersionSys->mServerVer->mABPath2HashDic.end();

	while(beginIte != endIte)
	{
		kvKey = beginIte->first;
		kvValue = beginIte->second;

		if (this->_isIncludeUpdateList(kvKey))
		{
			isFileInStreaming = false;
			isFileInPersistent = false;
			fileVerInfo = nullptr;

			isFileInPersistent = GVersionSys->mLocalVer->mABPath2Ver_P_Dic.containsKey(kvKey);

			if (isFileInPersistent)
			{
				fileVerInfo = GVersionSys->mLocalVer->mABPath2Ver_P_Dic[kvKey];
			}
			else
			{
				isFileInStreaming = GVersionSys->mLocalVer->mABPath2Ver_S_Dic.containsKey(kvKey);

				if (isFileInStreaming)
				{
					fileVerInfo = GVersionSys->mLocalVer->mABPath2Ver_S_Dic[kvKey];
				}
			}

			if (isFileInPersistent || isFileInStreaming)
			{
				isNeedUpdateFile = fileVerInfo->mFileMd5 != kvValue->mFileMd5;
				//isNeedUpdateFile = true;    // 强制更新

				if (isNeedUpdateFile)
				{
					this->mFileGroup->addLoadingPath(kvKey, kvValue);
					this->_loadOneUpdateFile(kvKey, kvValue);
				}
				else
				{
					this->mFileGroup->addLoadedPath(kvKey);
					this->mFileGroup->incCurNum();
				}
			}
			else
			{
				this->mFileGroup->addLoadingPath(kvKey, kvValue);
				this->_loadOneUpdateFile(kvKey, kvValue);
			}
		}
	}

	this->_checkUpdateEnd();

	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("AutoUpdateSys::loadAllUpdateFile, End", LogTypeId::eLogAutoUpdate);
	}
}

void AutoUpdateSys::_loadOneUpdateFile(std::string path, FileVerInfo* fileInfo)
{
	//string loadPath = UtilEngineWrap.combineVerPath(path, fileInfo.m_fileMd5);
	//mLoadingPath.add(loadPath);

	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log(UtilStr::Format("AutoUpdateSys::loadOneUpdateFile, add path = {0}", path), LogTypeId::eLogAutoUpdate);
	}

	if (GVersionSys->mLocalVer->mPath2Ver_P_Dic.containsKey(path))
	{
		//string checkPath = Path.Combine(MFileSys::getLocalWriteDir(), UtilLogic.combineVerPath(path, GVersionSys->mLocalVer->mPath2Ver_P_Dic[path].mFileMd5));

		std::string checkPath = UtilFileIO::combine(MFileSys::getLocalWriteDir(), path);

		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log(UtilStr::Format("AutoUpdateSys::loadOneUpdateFile, delete path = {0}", checkPath), LogTypeId::eLogAutoUpdate);
		}

		UtilFileIO::deleteFile(checkPath);     // 删除当前目录下已经有的 old 文件
	}

	//UtilEngineWrap.delFileNoVer(path);     // 删除当前目录下已经有的 old 文件

	AuxDownloader* auxDownload = MY_NEW AuxDownloader();
	auxDownload->setVersion(fileInfo->mFileMd5);
	auxDownload->setIsNeedUncompress(true);
	auxDownload->download(
		path,
		nullptr,
		&AutoUpdateSys::onLoadEventHandle,
		nullptr,
		nullptr,
		0,
		true,
		(int)DownloadType::eWebRequest
	);
}

void AutoUpdateSys::onLoadEventHandle(IDispatchObject* dispObj, uint uniqueId)
{
	std::string refPath;

	this->mFileGroup->incCurNum();

	AuxDownloader* downloader = (AuxDownloader*)dispObj;

	if (downloader->hasSuccessLoaded())
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log(UtilStr::Format("AutoUpdateSys::onLoadEventHandle, success, CurIndex = {0}, path = {1}", this->mFileGroup->getCurNum(), downloader->getOrigPath()), LogTypeId::eLogAutoUpdate);
		}

		refPath = downloader->getOrigPath();
		this->mFileGroup->addLoadedPath(refPath);
	}
	else if (downloader->hasFailed())
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log(UtilStr::Format("AutoUpdateSys::onLoadEventHandle, fail, CurNum = {0}, path = {1}", this->mFileGroup->getCurNum(), downloader->getOrigPath()), LogTypeId::eLogAutoUpdate);
		}

		refPath = downloader->getOrigPath();
		this->mFileGroup->addFailedPath(refPath);
	}

	refPath = downloader->getOrigPath();
	this->mFileGroup->removeLoadingPath(refPath);
	this->_checkUpdateEnd();

	downloader->dispose();
}

void AutoUpdateSys::_checkUpdateEnd()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log(UtilStr::Format("AutoUpdateSys::checkUpdateEnd, curNum = {0}, totalNum = {1}", this->mFileGroup->getCurNum(), this->mFileGroup->getTotalNum()), LogTypeId::eLogAutoUpdate);
	}

	if (this->mFileGroup->isCurEqTotal())
	{
		if (this->mFileGroup->hasLoadFailed())
		{
			this->setAutoUpdateErrorCode(AutoUpdateErrorCode::eErrorDownloadWebResFailed);
		}

		this->onUpdateEnd();
	}
}

void AutoUpdateSys::onUpdateEnd()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("AutoUpdateSys::onUpdateEnd, end", LogTypeId::eLogAutoUpdate);
		this->mFileGroup->logDownloadDetailInfo();
	}

	// 保存信息到本地
	if (this->isUpdateWebVersionPSuccessAndAllUpdateSuccess())     // 更新文件成功，将版本文件写入本地
	{
		// 保存 VerFileName::VER_MINI 版本文件和 VerFileName::VER_P 版本文件到 Persistent 文件夹
		GVersionSys->saveWebMiniOrPVerToPersistentPath();
		GVersionSys->updateLocalVerFile();
	}

	// 清理缓存重定向信息，因为之前信息可能是更新之前的定向，更新后需要重新生成一次
	GResRedirect->clearCacheInfo();

	// 通知上层
	this->mOnUpdateEndDispatch->dispatchEvent(nullptr);
}

// 是否在更新列表中
bool AutoUpdateSys::_isIncludeUpdateList(std::string path)
{
	bool ret = true;

	// 第一次从服务器上更新的时候，本地只有 StreamingAssets 目录下的 Version_S.txt ，但是 Version_P.txt 文件已经在 ServerVer.loadVerFile 文件中加载了，因此这里就不加载了
	if (VerFileName::VER_P == path)
	{
		ret = false;
	}

	return ret;
}

// 获取无需从服务器更新的文件数量
int AutoUpdateSys::_getExcludeUpdateFileNum()
{
	// VerFileName::VER_P 文件除外
	return 1;
}

MY_END_NAMESPACE