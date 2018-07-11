#include "MyProject.h"
#include "ServerVer.h"
#include "IDispatchObject.h"
#include "MacroDef.h"
#include "LogInc.h"
#include "MyMemoryInc.h"

MY_BEGIN_NAMESPACE(MyNS)

ServerVer::ServerVer()
{

}

void ServerVer::loadMiniVerFile()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys.log("ServerVer::loadMiniVerFile", LogTypeId::eLogAutoUpdate);
	}

	AuxDownloader* auxDownload = MY_NEW AuxDownloader();
	auxDownload.setVersion(UtilSysLibWrap.getRandomVersion());
	auxDownload.download(
		VerFileName::VER_MINI,
		nullptr,
		this->onMiniLoadEventHandle,
		nullptr,
		nullptr,
		0,
		false,
		(int)DownloadType.eWebRequest
	);
}

// 加载一个表完成
void ServerVer::_onMiniLoadEventHandle(IDispatchObject* dispObj, uint uniqueId)
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("ServerVer::onMiniLoadEventHandle", LogTypeId::eLogAutoUpdate);
	}

	AuxDownloader downloadItem = dispObj as AuxDownloader;

	if (downloadItem.hasSuccessLoaded())
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("ServerVer::onMiniLoadEventHandle, loaded", LogTypeId::eLogAutoUpdate);
		}

		byte[] textAsset = downloadItem.getBytes();

		if (textAsset != nullptr)
		{
			// Lzma 解压缩
			//byte[] outBytes = nullptr;
			//uint outLen = 0;
			//MLzma.DecompressStrLZMA(textAsset, (uint)textAsset.Length, ref outBytes, ref outLen);
			this->parseMiniFile(System.Text.Encoding.UTF8.GetString(textAsset));
		}

		this->mIsMiniLoadSuccess = true;
	}
	else if (downloadItem.hasFailed())
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("ServerVer::onMiniLoadEventHandle, error", LogTypeId::eLogAutoUpdate);
		}

		this->mIsMiniLoadSuccess = false;
	}

	downloadItem.dispose();

	this->mMiniLoadedDispatch.dispatchEvent(nullptr);
}

// 加载版本文件
void ServerVer::loadVerFile()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("ServerVer::loadVerFile", LogTypeId::eLogAutoUpdate);
	}

	AuxDownloader auxDownload = new AuxDownloader();
	auxDownload.setVersion(UtilSysLibWrap.getRandomVersion());
	auxDownload.download(
		VerFileName::VER_P,
		nullptr,
		this->onVerLoadEventHandle,
		nullptr,
		nullptr,
		0,
		false,
		(int)DownloadType.eWebRequest
	);
}

// 加载一个表完成
void ServerVer::_onVerLoadEventHandle(IDispatchObject* dispObj, uint uniqueId)
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("ServerVer::onVerLoadEventHandle", LogTypeId::eLogAutoUpdate);
	}

	AuxDownloader downloadItem = dispObj as AuxDownloader;

	if (downloadItem.hasSuccessLoaded())
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log(UtilStr::Format("ServerVer::onVerLoadEventHandle, loaded, origPath = {0}", downloadItem.getOrigPath()), LogTypeId::eLogAutoUpdate);
		}

		byte[] textAsset = downloadItem.getBytes();

		if (textAsset != nullptr)
		{
			this->loadFormText(System.Text.Encoding.UTF8.GetString(textAsset), this->mPath2HashDic, this->mABPath2HashDic);
		}

		this->mIsVerLoadSuccess = true;
	}
	else if (downloadItem.hasFailed())
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log(UtilStr::Format("ServerVer::onVerLoadEventHandle, failed, origPath = {0}", downloadItem.getOrigPath()), LogTypeId::eLogAutoUpdate);
		}

		this->mIsVerLoadSuccess = false;
	}

	this->mLoadedDispatch.dispatchEvent(nullptr);
}

void ServerVer::savePVerToPersistentPath()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("ServerVer::savePVerToPersistentPath, start", LogTypeId::eLogAutoUpdate);
	}

	string path = UtilFileIO::combine(MFileSys::msPersistentDataPath, VerFileName::VER_P);

	if (UtilFileIO::existFile(path))
	{
		UtilFileIO::deleteFile(path);
	}

	MDataStream dataStream = MY_NEW MDataStream(path, nullptr, MFileMode::eCreateNew, MFileAccess.eWrite);
	dataStream.open();

	string line = "";
	FileVerInfo fileVerInfo = nullptr;

	foreach(System.Collections.Generic.KeyValuePair<string, FileVerInfo> kv in this->mPath2HashDic.getData())
	{
		fileVerInfo = kv.Value;

		line = UtilStr::Format("{0}={1}={2}={3}={4}", fileVerInfo.mOrigPath, fileVerInfo.mResUniqueId, fileVerInfo.mLoadPath, fileVerInfo.mFileMd5, fileVerInfo.mFileSize);
		dataStream.writeLine(line);
	}

	dataStream.dispose();
	dataStream = nullptr;
}

MY_END_NAMESPACE