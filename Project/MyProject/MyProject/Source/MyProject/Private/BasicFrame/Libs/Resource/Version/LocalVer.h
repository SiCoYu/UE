#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 本地版本系统
 */
class LocalVer : public FileVerBase
{
    public MDictionary<string, FileVerInfo> mPath2Ver_R_Dic;    // Resources 文件夹版本
    public MDictionary<string, FileVerInfo> mPath2Ver_S_Dic;    // StreamingAssets 文件夹版本
    public MDictionary<string, FileVerInfo> mPath2Ver_P_Dic;    // Persistent 文件夹版本

    public MDictionary<string, FileVerInfo> mABPath2Ver_R_Dic;    // Resources 文件夹版本
    public MDictionary<string, FileVerInfo> mABPath2Ver_S_Dic;    // StreamingAssets 文件夹版本
    public MDictionary<string, FileVerInfo> mABPath2Ver_P_Dic;    // Persistent 文件夹版本

    public string mInstallMajorVersion;    // 安装时主版本
    public string mInstallMinorVersion;    // 安装时次版本
    public string mInstallPatchVersion;    // 安装时补丁版本

    protected MDataStream mMiniDataStream;      // Mini 版本
    protected MDataStream mRDataStream;         // Resources 版本
    protected MDataStream mSDataStream;         // StreamingAssets 版本
    protected MDataStream mPDataStream;         // Persistent 版本

    protected bool mIsMiniLoaded;       // Mini 
    protected bool mIsVerSLoaded;       // Version_S
    protected bool mIsVerPLoaded;       // Version_P

public:
	LocalVer();

	void loadAllLocalVer();
	string getInstallVersionString();
	void loadMiniVerFile();
	void loadStreamingAssetsMiniVerFile();
	void loadPersistentMiniVerFile();

protected:
	void onStreamingMiniLoadEventHandle(IDispatchObject dispObj, uint uniqueId);
	void onPersistentMiniLoadEventHandle(IDispatchObject dispObj, uint uniqueId);
	void onMiniLoadEventHandle(IDispatchObject dispObj, uint uniqueId);
    
public:
	// 加载 Resources 文件夹下文件对应的版本系统，目前没有了
	void loadLocalRVer();
	void onRVerLoaded(IDispatchObject dispObj, uint uniqueId);
    // Android 下 StreamingAssets 目录访问只能是异步的，因此需要等待这个访问完成才行
	void loadLocalSVer();
	void onSVerLoaded(IDispatchObject dispObj, uint uniqueId);
	void loadLocalPVer();
	void onPVerLoaded(IDispatchObject dispObj, uint uniqueId);

protected:
	void _onAllVerLoaded();

public:
	int getFileVerInfo(string origPath, ref FileVerInfo fileVerInfo, bool isABAsset);
    // 比较 Hash 码
protected:
	void _analyzeHash(
		FileVerInfo srcFileVerInfo,
		ResLoadType defaultResLoadType,
		ref FileVerInfo fileVerInfo,
		ref string md5,
		ref ResLoadType resLoadType
	);
};

MY_END_NAMESPACE