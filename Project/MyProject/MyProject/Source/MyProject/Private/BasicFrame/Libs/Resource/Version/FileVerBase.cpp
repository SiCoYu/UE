#include "MyProject.h"
#include "FileVerBase.h"
#include <vector>
#include "FileVerInfo.h"
#include "AddOnceAndCallOnceEventDispatch.h"
#include "UtilStr.h"
#include "MacroDef.h"
#include "MyMemoryInc.h"
#include "MDataStream.h"
#include "SafePointer.h"
#include "VerFileName.h"
#include "Symbolic.h"
#include "MFileSystem.h"
#include "UtilConvert.h"
#include "UtilFileIO.h"

MY_BEGIN_NAMESPACE(MyNS)

FileVerBase::FileVerBase()
{
	this->mIsMiniLoadSuccess = false;
	this->mIsVerLoadSuccess = false;

	this->mCurVer = "";           // 当前版本，当前日期，例如 201606091136-201606091136-0(主版本-次版本-补丁版本)
	this->mFileVerInfo = MY_NEW FileVerInfo();

	this->mMiniLoadedDispatch = MY_NEW AddOnceAndCallOnceEventDispatch();
	this->mLoadedDispatch = MY_NEW AddOnceAndCallOnceEventDispatch();

	this->mMajorVersion = "0";    // 主版本
	this->mMinorVersion = "0";    // 次版本
	this->mPatchVersion = "0";    // 补丁版本
	this->mTimeStamp = "0";       // 时间戳
}

std::string FileVerBase::getDetailVersionString()
{
	std::string ret = "";

	ret = UtilStr::Format("{0}-{1}-{2}-{3}", this->mMajorVersion, this->mMinorVersion, this->mPatchVersion, this->mTimeStamp);

	return ret;
}

std::string FileVerBase::getDotVersionString()
{
	std::string ret = "";

	ret = UtilStr::Format("{0}.{1}.{2}", this->mMajorVersion, this->mMinorVersion, this->mPatchVersion);

	return ret;
}

std::string FileVerBase::getVersionString()
{
	std::string ret = "";

	ret = UtilStr::Format("{0}-{1}-{2}", this->mMajorVersion, this->mMinorVersion, this->mPatchVersion);

	return ret;
}

void FileVerBase::saveMiniVerToPersistentPath()
{
	if (MacroDef::ENABLE_LOG)
	{
		GLogSys->log("FileVerBase::saveMiniVerToPersistentPath, start", LogTypeId::eLogAutoUpdate);
	}

	if (!this->mFileVerInfo->isNoVerInfo())
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log("FileVerBase::saveMiniVerToPersistentPath, isNoVerInfo is false", LogTypeId::eLogAutoUpdate);
		}

		std::string path = UtilFileIO::combine(MFileSystem::msPersistentDataPath, VerFileName::VER_MINI);

		if (UtilFileIO::existFile(path))
		{
			UtilFileIO::deleteFile(path);
		}

		MDataStream* dataStream = MY_NEW MDataStream(path, EventDispatchDelegate(), MFileMode::eCreateNew, MFileAccess::eWrite);
		dataStream->open();

		std::string line = UtilStr::Format("Version={0}", this->mCurVer);
		dataStream->writeLine(line);

		line = UtilStr::Format(
			"{0}={1}={2}={3}={4}", 
			this->mFileVerInfo->mOrigPath, 
			this->mFileVerInfo->mResUniqueId, 
			this->mFileVerInfo->mLoadPath, 
			this->mFileVerInfo->mFileMd5, 
			UtilConvert::convInt2Str(this->mFileVerInfo->mFileSize)
		);
		dataStream->writeLine(line);

		MY_SAFE_DISPOSE(dataStream);
	}
}

void FileVerBase::parseMiniFile(std::string text)
{
	std::string lineSplitStr = Symbolic::CR_LF;
	std::string equalSplitStr = Symbolic::SEPARATOR;
	std::vector<std::string> lineList;
	UtilStr::split(text, lineSplitStr, &lineList);
	int lineIdx = 0;
	std::vector<std::string> equalList;

	// 第一行是版本号
	lineIdx = 0;

	if (lineList.size() > 0)
	{
		UtilStr::removeLastCR(lineList[lineIdx]);
		UtilStr::split(lineList[lineIdx], equalSplitStr, &equalList);

		if (equalList.size() >= 2)
		{
			this->mCurVer = equalList[1];

			std::string verSplitStr = "&" ;
			std::vector<std::string> verStrList;
			UtilStr::split(this->mCurVer, verSplitStr, &verStrList);

			if (verStrList.size() == 4)
			{
				this->mMajorVersion = verStrList[0];
				this->mMinorVersion = verStrList[1];
				this->mPatchVersion = verStrList[2];
				this->mTimeStamp = verStrList[3];
			}
		}
		else
		{
			if (MacroDef::ENABLE_ERROR)
			{
				GLogSys->error(UtilStr::Format("FileVerBase::parseMiniFile, curversion error, content = {0}", text), LogTypeId::eErrorDownload);
			}
		}
	}
	else
	{
		if (MacroDef::ENABLE_ERROR)
		{
			GLogSys->error(UtilStr::Format("FileVerBase::parseMiniFile, LessEqual 0 error, content = {0}", text), LogTypeId::eErrorDownload);
		}
	}

	// 第二行是版本的版本
	lineIdx = 1;

	if (lineList.size() > 1)
	{
		UtilStr::removeLastCR(lineList[lineIdx]);

		UtilStr::split(lineList[lineIdx], equalSplitStr, &equalList);

		if (equalList.size() >= 5)
		{
			this->mFileVerInfo->mOrigPath = equalList[0];
			this->mFileVerInfo->mResUniqueId = equalList[1];
			this->mFileVerInfo->mLoadPath = equalList[2];
			this->mFileVerInfo->mFileMd5 = equalList[3];
			this->mFileVerInfo->mFileSize = UtilConvert::convStr2Int(equalList[4]);
		}
		else
		{
			if (MacroDef::ENABLE_ERROR)
			{
				GLogSys->error(UtilStr::Format("FileVerBase::parseMiniFile, version info error, content = {0}", text), LogTypeId::eErrorDownload);
			}
		}
	}
	else
	{
		if (MacroDef::ENABLE_ERROR)
		{
			GLogSys->error(UtilStr::Format("FileVerBase::parseMiniFile, less equal 1 error, content = {0}", text), LogTypeId::eErrorDownload);
		}
	}
}

// 这个主要是解析版本文件的
void FileVerBase::_loadFormText(std::string text, MDictionary<std::string, FileVerInfo*>& dic, MDictionary<std::string, FileVerInfo*>& abDic)
{
	std::string lineSplitStr = Symbolic::CR_LF;
	std::string equalSplitStr = Symbolic::SEPARATOR;
	std::vector<std::string> lineList;
	UtilStr::split(text, lineSplitStr, &lineList);

	int lineIdx = 0;
	std::vector<std::string> equalList;
	FileVerInfo* fileInfo = nullptr;

	while (lineIdx < lineList.size())
	{
		UtilStr::removeLastCR(lineList[lineIdx]);

		UtilStr::split(lineList[lineIdx], equalSplitStr, &equalList);

		if (equalList.size() == 5)
		{
			fileInfo = MY_NEW FileVerInfo();

			fileInfo->mOrigPath = equalList[0];
			fileInfo->mResUniqueId = equalList[1];
			fileInfo->mLoadPath = equalList[2];
			fileInfo->mFileMd5 = equalList[3];
			fileInfo->mFileSize = UtilConvert::convStr2Int(equalList[4]);

			//dic[fileInfo->mResUniqueId] = fileInfo;
			dic[fileInfo->mOrigPath] = fileInfo;

			if (!abDic.containsKey(fileInfo->mLoadPath))
			{
				abDic[fileInfo->mLoadPath] = fileInfo;
			}
		}
		else
		{
			if (MacroDef::ENABLE_ERROR)
			{
				GLogSys->error(UtilStr::Format("FileVerBase::loadFormText, version info error, content = {0}", lineList[lineIdx]), LogTypeId::eErrorDownload);
			}
		}

		++lineIdx;
	}

	int index = 0;
	int listLen = 0;

	if (!UtilStr::IsNullOrEmpty(lineSplitStr))
	{
		index = 0;
		listLen = lineSplitStr.length();

		while (index < listLen)
		{
			lineSplitStr[index] = '\0';
			index += 1;
		}

		lineSplitStr = nullptr;
	}

	if (!UtilStr::IsNullOrEmpty(equalSplitStr))
	{
		index = 0;
		listLen = equalSplitStr.length();

		while (index < listLen)
		{
			equalSplitStr[index] = '\0';
			index += 1;
		}

		equalSplitStr = nullptr;
	}

	if (lineList.size() > 0)
	{
		index = 0;
		listLen = lineList.size();

		while (index < listLen)
		{
			lineList[index] = "";
			index += 1;
		}

		lineList.clear();
	}

	if (equalList.size() > 0)
	{
		index = 0;
		listLen = equalList.size();

		while (index < listLen)
		{
			equalList[index] = nullptr;
			index += 1;
		}

		equalList.clear();
	}

	MY_SAFE_DISPOSE(fileInfo);
}

MY_END_NAMESPACE