#pragma once

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ServerVer;
class LocalVer;
class AddOnceAndCallOnceEventDispatch;

/**
 * @brief 版本系统，文件格式   path=value
 */
class VersionSys
{
public:
	ServerVer* mServerVer;
    LocalVer* mLocalVer;

    AddOnceAndCallOnceEventDispatch* mMiniLoadResultDispatch;
    AddOnceAndCallOnceEventDispatch* mLoadResultDispatch;

    bool mIsNeedUpdateApp;       // 是否需要更新 App
    bool mIsNeedUpdateVerFile;   // 是否需要更新版本文件

    std::string mMiniVer;    // mini 版本文件版本号

public:
	VersionSys();
	void init();

	void loadAllLocalVer();

	std::string getMajorVersion();
	std::string getMinorVersion();
	std::string getPatchVersion();
	std::string getTimeStamp();
	std::string getDetailVersionString();

	std::string getDotVersionString();
	std::string getVersionString();
	void loadWebMiniVerFile();
	void loadWebVerFile();
	void onWebMiniLoaded(IDispatchObject* dispObj, uint uniqueId);
	void onWebVerLoaded(IDispatchObject* dispObj, uint uniqueId);
	std::string getFileVer(std::string path);
    // 保存 VerFileName::VER_MINI 版本文件和 VerFileName::VER_P 版本文件到 Persistent 文件夹
	void saveWebMiniOrPVerToPersistentPath();
    // 如果 WebVerFile 版本文件更细了，就更新本地版本文件
	void updateLocalVerFile();
};

MY_END_NAMESPACE