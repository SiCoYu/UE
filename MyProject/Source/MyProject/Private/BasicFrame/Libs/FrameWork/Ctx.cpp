#include "MyProject.h"
#include "Ctx.h"
#include "EngineData.h"
#include "INetMgr.h"
#include "UIMgr.h"
#include "NetMgr.h"
#include "EngineApi.h"
#include "TableSys.h"
#include "ShareData.h"
#include "NetDispList.h"
#include "LogSys.h"
#include "Config.h"
#include "LocalFileSys.h"
#include "PoolSys.h"
#include "UIAssetMgr.h"
#include "ResLoadMgr.h"

#ifdef ENABLE_UNIT_TEST
	#include "Test.h"
#endif

// 偏特化
template<> Ctx* Ctx::Singleton<Ctx>::msSingleton = 0;

Ctx::Ctx()
{
	
}

Ctx::~Ctx()
{
	delete mUiMgr;
	delete mEngineData;
	delete mNetMgr;
	delete mTableSys;

#ifdef USE_EXTERN_THREAD
	delete m_pStdoutLog;
#endif

#ifdef ENABLE_UNIT_TEST
	delete m_test;
#endif

	delete mLogSys;
	delete mNetDispList;
	delete mShareData;
	delete mConfig;
	delete mLocalFileSys;

	delete mSandboxPlatformFile;
}

void Ctx::init()
{
	mShareData = new ShareData();
	mNetDispList = new NetDispList();
	mLogSys = new LogSys();
	mEngineData = new EngineData();
#ifdef USE_EXTERN_THREAD
	m_pStdoutLog = new StdoutLog();
#endif

	mUiMgr = new UIMgr();
	mTableSys = new TableSys();
	mConfig = new Config();
	mLocalFileSys = new LocalFileSys();
#ifdef	USE_EXTERN_THREAD
	mNetMgr = new NetMgr(getStdLog());
#else
	mNetMgr = new NetMgr();
#endif

	// 初始化 SandBox 文件系统
	mSandboxPlatformFile = new FSandboxPlatformFile(false);
	//FString OutputDirectory = GetOutputDirectoryOverride();
	FString OutputDirectory = FPaths::GameDir();
	mSandboxPlatformFile->Initialize(&FPlatformFileManager::Get().GetPlatformFile(), *FString::Printf(TEXT("-sandbox=\"%s\""), *OutputDirectory));

	// 挂在目录
	EngineApi::InsertMountPoint("/CacheData/", "E:/Self/Self/unreal/UE-GIT/UE-BP");
}

void Ctx::beginPlay()
{
#ifdef ENABLE_UNIT_TEST
	m_test = new Test();
	m_test->runTest();
#endif

	testApi();

	//GCtx->setUiMgr(new UIManager());
	//GCtx->setEngineApi(new EngineApi());
	//GCtx->setNetMgr(new NetMgr(Ctx::getSingletonPtr()->getStdLog()));

	// test
	//GUiMgr->loadForm(eUIPack);
	GNetMgr->openSocket("192.168.124.26", 10002);
}

void Ctx::setUiMgr(UIMgr* uiMgr)
{
	mUiMgr = uiMgr;
}

UIMgr* Ctx::getUIMgr()
{
	return mUiMgr;
}

EngineData* Ctx::getEngineData()
{
	return mEngineData;
}

void Ctx::setNetMgr(INetMgr* pINetMgr)
{
	mNetMgr = pINetMgr;
}

INetMgr* Ctx::getNetMgr()
{
	return mNetMgr;
}

#ifdef USE_EXTERN_THREAD
StdoutLog* Ctx::getStdLog()
{
	return m_pStdoutLog;
}
#endif

TableSys* Ctx::getTableSys()
{
	return mTableSys;
}

LogSys* Ctx::getLogSys()
{
	return mLogSys;
}

ShareData* Ctx::getShareData()
{
	return mShareData;
}

NetDispList* Ctx::getNetDispList()
{
	return mNetDispList;
}

Config* Ctx::getConfig()
{
	return mConfig;
}

LocalFileSys* Ctx::getLocalFileSys()
{
	return mLocalFileSys;
}

PoolSys* Ctx::getPoolSys()
{
	return mPoolSys;
}

UIAssetMgr* Ctx::getUiAssetMgr()
{
	return mUiAssetMgr;
}

ResLoadMgr* Ctx::getResLoadMgr()
{
	return mResLoadMgr;
}

FSandboxPlatformFile* Ctx::getSandboxPlatformFile()
{
	return this->mSandboxPlatformFile;
}

void Ctx::testApi()
{
	EngineApi::GameUserDir();
}