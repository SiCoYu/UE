#pragma once

#include <string>
#include "TypeDef.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ServerVer;
class LocalVer;
class AddOnceAndCallOnceEventDispatch;
class IDispatchObject;

/**
 * @brief 版本系统，文件格式   path=value
 */
class VersionSysN : public GObject
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
	VersionSysN();

	// 继承 GObject 就会有链接错误
	//2>Ctx.cpp.obj : error LNK2019 : unresolved external symbol "public: void __cdecl MyNS::VersionSys::init(void)" (? init@VersionSys@MyNS@@QEAAXXZ) referenced in function "protected: void __cdecl MyNS::Ctx::_execInit(void)" (? _execInit@Ctx@MyNS@@IEAAXXZ)
	//	2>Ctx.cpp.obj : error LNK2019 : unresolved external symbol "public: void __cdecl MyNS::VersionSys::dispose(void)" (? dispose@VersionSys@MyNS@@QEAAXXZ) referenced in function "protected: void __cdecl MyNS::Ctx::_preDispose(void)" (? _preDispose@Ctx@MyNS@@IEAAXXZ)
	//virtual void init() override;
	//virtual void dispose() override;
	void init();
	void dispose();

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
	void onWebMiniLoaded(uint eventId, IDispatchObject* dispObj);
	void onWebVerLoaded(uint eventId, IDispatchObject* dispObj);
	std::string getFileVer(std::string path);
    // 保存 VerFileName::VER_MINI 版本文件和 VerFileName::VER_P 版本文件到 Persistent 文件夹
	void saveWebMiniOrPVerToPersistentPath();
    // 如果 WebVerFile 版本文件更细了，就更新本地版本文件
	void updateLocalVerFile();
};

MY_END_NAMESPACE