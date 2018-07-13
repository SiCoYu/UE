#pragma once

#include <string>
#include "FileVerBase.h"
#include "MDictionary.h"
#include "ResLoadType.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class FileVerInfo;
class MDataStream;
class IDispatchObject;

/**
 * @brief 本地版本系统
 */
class LocalVer : public FileVerBase
{
public:
	MDictionary<std::string, FileVerInfo*> mPath2Ver_R_Dic;    // Resources 文件夹版本
    MDictionary<std::string, FileVerInfo*> mPath2Ver_S_Dic;    // StreamingAssets 文件夹版本
    MDictionary<std::string, FileVerInfo*> mPath2Ver_P_Dic;    // Persistent 文件夹版本

    MDictionary<std::string, FileVerInfo*> mABPath2Ver_R_Dic;    // Resources 文件夹版本
    MDictionary<std::string, FileVerInfo*> mABPath2Ver_S_Dic;    // StreamingAssets 文件夹版本
    MDictionary<std::string, FileVerInfo*> mABPath2Ver_P_Dic;    // Persistent 文件夹版本

    std::string mInstallMajorVersion;    // 安装时主版本
	std::string mInstallMinorVersion;    // 安装时次版本
	std::string mInstallPatchVersion;    // 安装时补丁版本

protected:
	MDataStream* mMiniDataStream;      // Mini 版本
    MDataStream* mRDataStream;         // Resources 版本
    MDataStream* mSDataStream;         // StreamingAssets 版本
    MDataStream* mPDataStream;         // Persistent 版本

    bool mIsMiniLoaded;       // Mini 
    bool mIsVerSLoaded;       // Version_S
    bool mIsVerPLoaded;       // Version_P

public:
	LocalVer();

	void loadAllLocalVer();
	std::string getInstallVersionString();
	void loadMiniVerFile();
	void loadStreamingAssetsMiniVerFile();
	void loadPersistentMiniVerFile();

protected:
	void onStreamingMiniLoadEventHandle(uint eventId, IDispatchObject* dispObj);
	void onPersistentMiniLoadEventHandle(uint eventId, IDispatchObject* dispObj);
	void onMiniLoadEventHandle(uint eventId, IDispatchObject* dispObj);
    
public:
	// 加载 Resources 文件夹下文件对应的版本系统，目前没有了
	void loadLocalRVer();
	void onRVerLoaded(uint eventId, IDispatchObject* dispObj);
    // Android 下 StreamingAssets 目录访问只能是异步的，因此需要等待这个访问完成才行
	void loadLocalSVer();
	void onSVerLoaded(uint eventId, IDispatchObject* dispObj);
	void loadLocalPVer();
	void onPVerLoaded(uint eventId, IDispatchObject* dispObj);

protected:
	void _onAllVerLoaded();

public:
	int getFileVerInfo(std::string& origPath, FileVerInfo* fileVerInfo, bool isABAsset);
    // 比较 Hash 码
protected:
	void _analyzeHash(
		FileVerInfo* srcFileVerInfo,
		ResLoadType defaultResLoadType,
		FileVerInfo* fileVerInfo,
		std::string& md5,
		ResLoadType resLoadType
	);
};

MY_END_NAMESPACE