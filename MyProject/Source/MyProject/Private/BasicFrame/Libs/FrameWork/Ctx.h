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
class UIAssetMgr;
class ResLoadMgr;

#ifdef ENABLE_UNIT_TEST
	class Test;
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
	UIAssetMgr* mUiAssetMgr;
	ResLoadMgr* mResLoadMgr;

	// F:\File\opensource\UnrealEngine-4.0\UnrealEngine-git\Engine\Source\Editor\UnrealEd\Private\Commandlets\CookCommandlet.cpp
	FSandboxPlatformFile* mSandboxPlatformFile;

#ifdef USE_EXTERN_THREAD
	StdoutLog* m_pStdoutLog;
#endif

#ifdef ENABLE_UNIT_TEST
	Test* m_test;
#endif

public:
	Ctx();
	~Ctx();

	void init();
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
	UIAssetMgr* getUiAssetMgr();
	ResLoadMgr* getResLoadMgr();
	FSandboxPlatformFile* getSandboxPlatformFile();

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
#define GUiAssetMgr GCtx->getUiAssetMgr()
#define GResLoadMgr GCtx->getResLoadMgr()
#define GSandboxPlatformFile GCtx->getSandboxPlatformFile()

#endif				// __CTX_H