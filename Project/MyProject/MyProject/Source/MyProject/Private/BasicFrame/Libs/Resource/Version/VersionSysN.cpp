#include "MyProject.h"
#include "VersionSysN.h"
#include "UtilMath.h"
#include "AddOnceAndCallOnceEventDispatch.h"
#include "ServerVer.h"
#include "LocalVer.h"
#include "UtilConvert.h"
#include "MacroDef.h"
#include "EventDispatchDelegate.h"
#include "IDispatchObject.h"
#include "FileVerInfo.h"

MY_BEGIN_NAMESPACE(MyNS)

VersionSysN::VersionSysN()
{
	this->mMiniVer = UtilConvert::convInt2Str(UtilMath::range(0, UtilMath::msIntMaxValue));
	this->mMiniLoadResultDispatch = MY_NEW AddOnceAndCallOnceEventDispatch();
	this->mLoadResultDispatch = MY_NEW AddOnceAndCallOnceEventDispatch();

	this->mServerVer = MY_NEW ServerVer();
	this->mLocalVer = MY_NEW LocalVer();
}

void VersionSysN::init()
{

}

void VersionSysN::dispose()
{

}

void VersionSysN::loadAllLocalVer()
{
	this->mLocalVer->loadAllLocalVer();
}

std::string VersionSysN::getMajorVersion()
{
	std::string ret = "";

	if (this->mServerVer->mIsMiniLoadSuccess)
	{
		ret = this->mServerVer->mMajorVersion;
	}
	else
	{
		ret = this->mLocalVer->mMajorVersion;
	}

	return ret;
}

std::string VersionSysN::getMinorVersion()
{
	std::string ret = "";

	if (this->mServerVer->mIsMiniLoadSuccess)
	{
		ret = this->mServerVer->mMinorVersion;
	}
	else
	{
		ret = this->mLocalVer->mMinorVersion;
	}

	return ret;
}

std::string VersionSysN::getPatchVersion()
{
	std::string ret = "";

	if (this->mServerVer->mIsMiniLoadSuccess)
	{
		ret = this->mServerVer->mPatchVersion;
	}
	else
	{
		ret = this->mLocalVer->mPatchVersion;
	}

	return ret;
}

std::string VersionSysN::getTimeStamp()
{
	std::string ret = "";

	if (this->mServerVer->mIsMiniLoadSuccess)
	{
		ret = this->mServerVer->mTimeStamp;
	}
	else
	{
		ret = this->mLocalVer->mTimeStamp;
	}

	return ret;
}

std::string VersionSysN::getDetailVersionString()
{
	std::string ret = "";

	if (this->mServerVer->mIsMiniLoadSuccess)
	{
		ret = this->mServerVer->getDetailVersionString();
	}
	else
	{
		ret = this->mLocalVer->getDetailVersionString();
	}

	return ret;
}

std::string VersionSysN::getDotVersionString()
{
	std::string ret = "";

	if (this->mServerVer->mIsMiniLoadSuccess)
	{
		ret = this->mServerVer->getDotVersionString();
	}
	else
	{
		ret = this->mLocalVer->getDotVersionString();
	}

	return ret;
}

std::string VersionSysN::getVersionString()
{
	std::string ret = "";

	if (this->mServerVer->mIsMiniLoadSuccess)
	{
		ret = this->mServerVer->getVersionString();
	}
	else
	{
		ret = this->mLocalVer->getVersionString();
	}

	return ret;
}

void VersionSysN::loadWebMiniVerFile()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("VersionSys::loadWebMiniVerFile", LogTypeId::eLogAutoUpdate);
	}

	this->mServerVer->mMiniLoadedDispatch->addEventHandle(
		MakeEventDispatchDelegate(
			this, 
			&VersionSysN::onWebMiniLoaded,
			(uint)0
		)
	);
	this->mServerVer->loadMiniVerFile();
}

void VersionSysN::loadWebVerFile()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("VersionSys::loadWebVerFile, start", LogTypeId::eLogAutoUpdate);
	}

	if (this->mLocalVer->mIsVerLoadSuccess)
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("VersionSys::loadWebVerFile, mLocalVer->mIsVerLoadSuccess is true", LogTypeId::eLogAutoUpdate);
		}

		if (this->mIsNeedUpdateVerFile)
		{
			if (MacroDef::ENABLE_LOG)
			{
				GLogSys->log("VersionSys::loadWebVerFile, mIsNeedUpdateVerFile is true", LogTypeId::eLogAutoUpdate);
			}

			this->mServerVer->mLoadedDispatch->addEventHandle(
				MakeEventDispatchDelegate(
					this,
					&VersionSysN::onWebVerLoaded,
					(uint)0
				)
			);
			this->mServerVer->loadVerFile();
		}
		else
		{
			if (MacroDef::ENABLE_LOG)
			{
				GLogSys->log("VersionSys::loadWebVerFile, mIsNeedUpdateVerFile is false", LogTypeId::eLogAutoUpdate);
			}

			this->mLoadResultDispatch->dispatchEvent(nullptr);
		}
	}
	else
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("VersionSys::loadWebVerFile, mLocalVer->mIsVerLoadSuccess is false", LogTypeId::eLogAutoUpdate);
		}

		if (this->mIsNeedUpdateVerFile)
		{
			if (MacroDef::ENABLE_LOG)
			{
				GLogSys->log("VersionSys::loadWebVerFile, mIsNeedUpdateVerFile is true", LogTypeId::eLogAutoUpdate);
			}

			this->mServerVer->mLoadedDispatch->addEventHandle(
				MakeEventDispatchDelegate(
					this,
					&VersionSysN::onWebVerLoaded,
					(uint)0
				)
			);
			this->mServerVer->loadVerFile();
		}
		else
		{
			if (MacroDef::ENABLE_LOG)
			{
				GLogSys->log("VersionSys::loadWebVerFile, mIsNeedUpdateVerFile is false", LogTypeId::eLogAutoUpdate);
			}

			this->mLoadResultDispatch->dispatchEvent(nullptr);
		}
	}
}

void VersionSysN::onWebMiniLoaded(uint eventId, IDispatchObject* dispObj)
{
	if (this->mServerVer->mIsMiniLoadSuccess)
	{
		// 删除旧 mini 版本，修改新版本文件名字
		//UtilFileIO::deleteFile(Path.Combine(MFileSystem::getLocalWriteDir(), VerFileName::VER_P));
		// 修改新的版本文件名字
		//UtilFileIO::renameFile(UtilLogic.combineVerPath(Path.Combine(MFileSystem::getLocalWriteDir(), VerFileName::VER_MINI), m_miniVer), Path.Combine(MFileSystem::getLocalWriteDir(), VerFileName::VER_MINI));

		this->mIsNeedUpdateApp = (this->mLocalVer->mMajorVersion != this->mServerVer->mMajorVersion);      // 如果版本不一致，需要重新加载 App
		this->mIsNeedUpdateVerFile = (this->mLocalVer->mFileVerInfo->mFileMd5 != this->mServerVer->mFileVerInfo->mFileMd5);      // 如果版本不一致，需要重新加载版本文件

																															 //this->mIsNeedUpdateVerFile = true;         // 测试强制更新

		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log(UtilStr::Format("VersionSys::onWebMiniLoaded, loaded, mIsNeedUpdateApp = {0}, mIsNeedUpdateVerFile = {1}", this->mIsNeedUpdateApp, this->mIsNeedUpdateVerFile), LogTypeId::eLogAutoUpdate);
		}
	}
	else
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("VersionSys::onWebMiniLoaded, failed", LogTypeId::eLogAutoUpdate);
		}

		// 如果没有加载到服务器版本文件，就不用更新了
		this->mIsNeedUpdateApp = false;
		this->mIsNeedUpdateVerFile = false;
	}

	this->mMiniLoadResultDispatch->dispatchEvent(nullptr);
}

void VersionSysN::onWebVerLoaded(uint eventId, IDispatchObject* dispObj)
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("VersionSys::onWebVerLoaded", LogTypeId::eLogAutoUpdate);
	}

	this->mLoadResultDispatch->dispatchEvent(nullptr);
}

std::string VersionSysN::getFileVer(std::string path)
{
	std::string ret = "";

	if (this->mIsNeedUpdateVerFile)
	{
		if (this->mServerVer->mPath2HashDic.containsKey(path))
		{
			ret = this->mServerVer->mPath2HashDic[path]->mFileMd5;
		}
	}
	else
	{
		if (this->mLocalVer->mPath2Ver_P_Dic.containsKey(path))
		{
			ret = this->mLocalVer->mPath2Ver_P_Dic[path]->mFileMd5;
		}
	}

	return ret;
}

// 保存 VerFileName::VER_MINI 版本文件和 VerFileName::VER_P 版本文件到 Persistent 文件夹
void VersionSysN::saveWebMiniOrPVerToPersistentPath()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("VersionSys::saveWebMiniOrPVerToPersistentPath", LogTypeId::eLogAutoUpdate);
	}

	this->mServerVer->saveMiniVerToPersistentPath();

	if (this->mIsNeedUpdateVerFile)
	{
		this->mServerVer->savePVerToPersistentPath();
	}
}

// 如果 WebVerFile 版本文件更细了，就更新本地版本文件
void VersionSysN::updateLocalVerFile()
{
	//if (nullptr != this->mLocalVer->mPath2Ver_P_Dic)
	{
		this->mLocalVer->mPath2Ver_P_Dic.clear();
		this->mLocalVer->mABPath2Ver_P_Dic.clear();
	}

	this->mLocalVer->mPath2Ver_P_Dic = this->mServerVer->mPath2HashDic;
	this->mLocalVer->mABPath2Ver_P_Dic = this->mServerVer->mABPath2HashDic;

	//this->mServerVer->mPath2HashDic = nullptr;
	//this->mServerVer->mABPath2HashDic = nullptr;
}

MY_END_NAMESPACE