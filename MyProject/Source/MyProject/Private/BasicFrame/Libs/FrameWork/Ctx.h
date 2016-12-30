#ifndef __Ctx_H
#define __Ctx_H

#include "Singleton.h"
#include "PlatformDefine.h"

#ifdef USE_EXTERN_THREAD
	#include <Sockets/StdoutLog.h>
#endif

#include "Containers/UnrealString.h"
#include "IPlatformFileSandboxWrapper.h"

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

#ifdef ENABLE_UNIT_TEST
	class TestMain;
#endif

class Ctx : public Singleton<Ctx>
{
protected:
	UIMgr* mUiMgr;
	EngineData* mEngineData;
	INetMgr* mNetMgr;
	TableSys* mTableSys;
	LogSys* mLogSys;
	ShareData* mShareData;
	NetDispList* mNetDispList;
	Config* mConfig;
	LocalFileSys* mLocalFileSys;
	PoolSys* mPoolSys;
	ResLoadMgr* mResLoadMgr;
	ClassAssetInsMgr* mClassAssetInsMgr;
	ObjectAssetInsMgr* mObjectAssetInsMgr;

	FMyStreamableManager* mMyStreamableManager;
	DownloadMgr* mDownloadMgr;
	MFileSys* mFileSys;

#ifdef USE_EXTERN_THREAD
	StdoutLog* mStdoutLog;
#endif

#ifdef ENABLE_UNIT_TEST
	TestMain* mTestMain;
#endif

public:
	Ctx();
	~Ctx();

	void construct();
	void init();
	void beginPlay();

	void setUiMgr(UIMgr* uiMgr);
	UIMgr* getUIMgr();

	EngineData* getEngineData();
	void setNetMgr(INetMgr* pINetMgr);
	INetMgr* getNetMgr();
	TableSys* getTableSys();
	LogSys* getLogSys();
	ShareData* getShareData();
	NetDispList* getNetDispList();
	Config* getConfig();
	LocalFileSys* getLocalFileSys();
	PoolSys* getPoolSys();
	ResLoadMgr* getResLoadMgr();

	ClassAssetInsMgr* getClassAssetInsMgr();
	ObjectAssetInsMgr* getObjectAssetInsMgr();

	FMyStreamableManager* getMyStreamableManager();
	DownloadMgr* getDownloadMgr();
	MFileSys* getFileSys();

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
#define GLocalFileSys GCtx->getLocalFileSys()
#define GPoolSys GCtx->getPoolSys()
#define GResLoadMgr GCtx->getResLoadMgr()

#define GClassAssetInsMgr GCtx->getClassAssetInsMgr()
#define GObjectAssetInsMgr GCtx->getObjectAssetInsMgr()

#define GSandboxPlatformFile GCtx->getSandboxPlatformFile()
#define GMyStreamableManager GCtx->getMyStreamableManager()
#define GDownloadMgr GCtx->getDownloadMgr()
#define GFileSys GCtx->getFileSys()

#endif				// __CTX_H