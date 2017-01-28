#ifndef __Ctx_H
#define __Ctx_H

#include "Singleton.h"
#include "PlatformDefine.h"

#ifdef USE_EXTERN_THREAD
	#include <Sockets/StdoutLog.h>
#endif

#include "Containers/UnrealString.h"
#include "IPlatformFileSandboxWrapper.h"
#include "CoreInc.h"

class UIMgr;
class UGameInstance;
class EngineData;
class INetMgr;
class TableSys;
class LogSys;
class ShareData;
class NetDispList;
class Config;
class LocalFileSys;
class PoolSys;

class ResLoadMgr;
class ClassAssetInsMgr;
class ObjectAssetInsMgr;
class FMyStreamableManager;
class DownloadMgr;
class MFileSys;
class SystemSetting;
class LuaSystem;
class ISceneEventCB;
class MyLatentActionManager;

class SceneSys;
class SystemTimeData;
class SystemFrameData;
class ProcessSys;
class EngineLoop;
class DelayLoadMgr

class Ctx : public Singleton<Ctx>
{
protected:
	bool mIsInit;
	MySharedPtr<UIMgr> mUiMgr;
	MySharedPtr<EngineData> mEngineData;
	MySharedPtr<INetMgr> mNetMgr;
	MySharedPtr<TableSys> mTableSys;
	MySharedPtr<LogSys> mLogSys;
	MySharedPtr<ShareData> mShareData;
	MySharedPtr<NetDispList> mNetDispList;
	MySharedPtr<Config> mConfig;
	MySharedPtr<LocalFileSys> mLocalFileSys;
	MySharedPtr<PoolSys> mPoolSys;
	MySharedPtr<ResLoadMgr> mResLoadMgr;
	MySharedPtr<ClassAssetInsMgr> mClassAssetInsMgr;
	MySharedPtr<ObjectAssetInsMgr> mObjectAssetInsMgr;

	MySharedPtr<FMyStreamableManager> mMyStreamableManager;
	MySharedPtr<DownloadMgr> mDownloadMgr;
	MySharedPtr<MFileSys> mFileSys;
	MySharedPtr<SystemSetting> mSystemSetting;
	MySharedPtr<LuaSystem> mLuaSystem;
	MySharedPtr<ISceneEventCB> mSceneEventCB;
	MySharedPtr<MyLatentActionManager> mMyLatentActionManager;

	MySharedPtr<SceneSys> mSceneSys;
	MySharedPtr<SystemTimeData> mSystemTimeData;
	MySharedPtr<SystemFrameData> mSystemFrameData;
	MySharedPtr<ProcessSys> mProcessSys;
	MySharedPtr<EngineLoop> mEngineLoop;
	MySharedPtr<DelayLoadMgr> mDelayLoadMgr;

#ifdef USE_EXTERN_THREAD
	MySharedPtr<StdoutLog*> mStdoutLog;
#endif

public:
	Ctx();
	~Ctx();

	void construct();
	void init();
	void dispose();
	void beginPlay();
	void mainLoop();

	void setUiMgr(UIMgr* uiMgr);
	MySharedPtr<UIMgr> getUIMgr();

	MySharedPtr<EngineData> getEngineData();
	void setNetMgr(INetMgr* pINetMgr);
	MySharedPtr<INetMgr> getNetMgr();
	MySharedPtr<TableSys> getTableSys();
	MySharedPtr<LogSys> getLogSys();
	MySharedPtr<ShareData> getShareData();
	MySharedPtr<NetDispList> getNetDispList();
	MySharedPtr<Config> getConfig();
	MySharedPtr<LocalFileSys> getLocalFileSys();
	MySharedPtr<PoolSys> getPoolSys();
	MySharedPtr<ResLoadMgr> getResLoadMgr();

	MySharedPtr<ClassAssetInsMgr> getClassAssetInsMgr();
	MySharedPtr<ObjectAssetInsMgr> getObjectAssetInsMgr();

	MySharedPtr<FMyStreamableManager> getMyStreamableManager();
	MySharedPtr<DownloadMgr> getDownloadMgr();
	MySharedPtr<MFileSys> getFileSys();
	MySharedPtr<SystemSetting> getSystemSetting();
	MySharedPtr<LuaSystem> getLuaSystem();
	MySharedPtr<ISceneEventCB> getSceneEventCB();
	MySharedPtr<MyLatentActionManager> getMyLatentActionManager();

	MySharedPtr<SceneSys> getSceneSys();
	MySharedPtr<SystemTimeData> getSystemTimeData();
	MySharedPtr<SystemFrameData> getSystemFrameData();
	MySharedPtr<ProcessSys> getProcessSys();
	MySharedPtr<EngineLoop> getEngineLoop();
	MySharedPtr<DelayLoadMgr> getDelayLoadMgr();

	/**
	 *@brief 测试 Api，以后放到 UnitTest 中去
	 */
	void testApi();

#ifdef USE_EXTERN_THREAD
	StdoutLog* getStdLog();
#endif
};

#define GCtx Ctx::getSingletonPtr()
#define GTableSys GCtx->getTableSys()
#define GNetMgr GCtx->getNetMgr()
#define GUiMgr GCtx->getUIMgr()
#define GLogSys GCtx->getLogSys()
#define GEngineData GCtx->getEngineData()
#define GShareData GCtx->getShareData()
#define GNetDispList GCtx->getNetDispList()
#define GCfg GCtx->getConfig()
#define GPoolSys GCtx->getPoolSys()
#define GResLoadMgr GCtx->getResLoadMgr()

#define GClassAssetInsMgr GCtx->getClassAssetInsMgr()
#define GObjectAssetInsMgr GCtx->getObjectAssetInsMgr()

#define GSandboxPlatformFile GCtx->getSandboxPlatformFile()
#define GMyStreamableManager GCtx->getMyStreamableManager()
#define GDownloadMgr GCtx->getDownloadMgr()
#define GFileSys GCtx->getFileSys()
#define GSandboxPlatformFile GCtx->getFileSys()->getSandboxPlatformFile()
#define GSystemSetting GCtx->getSystemSetting()
#define GLuaSystem GCtx->getLuaSystem()
#define GSceneEventCB GCtx->getSceneEventCB()
#define GMyLatentActionManager GCtx->getMyLatentActionManager()

#define GSceneSys GCtx->getSceneSys()
#define GSystemTimeData GCtx->getSystemTimeData()
#define GSystemFrameData GCtx->getSystemFrameData()
#define GProcessSys GCtx->getProcessSys()
#define GEngineLoop GCtx->getEngineLoop()
#define GDelayLoadMgr GCtx->getDelayLoadMgr()

#endif				// __CTX_H