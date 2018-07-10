#pragma once

#include <string.h>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceAndCallOnceEventDispatch;

class FileVerBase
{
public:
	std::string mCurVer;              // 当前程序的版本号
    FileVerInfo* mFileVerInfo;    // 这个主要是记录文件版本的版本

	std::string mMajorVersion;    // 主版本
	std::string mMinorVersion;    // 次版本
	std::string mPatchVersion;    // 补丁版本
	std::string mTimeStamp;       // 时间戳

    bool mIsMiniLoadSuccess;
    bool mIsVerLoadSuccess;

    AddOnceAndCallOnceEventDispatch* mMiniLoadedDispatch;
    AddOnceAndCallOnceEventDispatch mLoadedDispatch;

public:
	FileVerBase();

	std::string getDetailVersionString();
	std::string getDotVersionString();

	std::string getVersionString();
	void saveMiniVerToPersistentPath();
	void parseMiniFile(string text);
	void _loadFormText(string text, MDictionary<string, FileVerInfo> dic, MDictionary<string, FileVerInfo> abDic);
};

MY_END_NAMESPACE