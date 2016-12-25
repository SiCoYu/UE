#include "MyProject.h"
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

#include "ResLoadMgr.h"
#include "UIAssetMgr.h"
#include "ClassAssetMgr.h"
#include "ObjectAssetMgr.h"
#include "MyStreamableManager.h"

#include "Ctx.h"

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
	delete this->mUiMgr;
	delete this->mEngineData;
	delete this->mNetMgr;
	delete this->mTableSys;

#ifdef USE_EXTERN_THREAD
	delete this->mStdoutLog;
#endif

#ifdef ENABLE_UNIT_TEST
	delete this->mTest;
#endif

	delete this->mLogSys;
	delete this->mNetDispList;
	delete this->mShareData;
	delete this->mConfig;
	delete this->mLocalFileSys;

	delete this->mSandboxPlatformFile;

	delete this->mResLoadMgr;
	delete this->mUiAssetMgr;
	delete this->mClassAssetMgr;
	delete this->mObjectAssetMgr;

	delete this->mMyStreamableManager;
}

void Ctx::construct()
{
	this->mShareData = new ShareData();
	this->mNetDispList = new NetDispList();
	this->mLogSys = new LogSys();
	this->mEngineData = new EngineData();
#ifdef USE_EXTERN_THREAD
	this->mStdoutLog = new StdoutLog();
#endif

	this->mMyStreamableManager = new MyStreamableManager();
	this->mResLoadMgr = new ResLoadMgr();
	this->mUiAssetMgr = new UIAssetMgr();
	this->mClassAssetMgr = new ClassAssetMgr();
	this->mObjectAssetMgr = new ObjectAssetMgr();

	this->mUiMgr = new UIMgr();
	this->mTableSys = new TableSys();
	this->mConfig = new Config();
	this->mLocalFileSys = new LocalFileSys();
#ifdef	USE_EXTERN_THREAD
	this->mNetMgr = new NetMgr(getStdLog());
#else
	this->mNetMgr = new NetMgr();
#endif

	// 初始化 SandBox 文件系统
	this->mSandboxPlatformFile = new FSandboxPlatformFile(false);
}

void Ctx::init()
{
	this->mMyStreamableManager->init();
	this->mUiMgr->init();
	this->mResLoadMgr->init();
	this->mUiAssetMgr->init();

	// 初始化 SandBox 文件系统
	//mSandboxPlatformFile = new FSandboxPlatformFile(false);
	//FString OutputDirectory = GetOutputDirectoryOverride();
	FString OutputDirectory = FPaths::GameDir();
	this->mSandboxPlatformFile->Initialize(&FPlatformFileManager::Get().GetPlatformFile(), *FString::Printf(TEXT("-sandbox=\"%s\""), *OutputDirectory));

	// 挂在目录
	EngineApi::InsertMountPoint("/CacheData/", "E:/Self/Self/unreal/UE-GIT/UE-BP");
}

void Ctx::beginPlay()
{
	this->init();

#ifdef ENABLE_UNIT_TEST
	this->mTest = new Test();
	this->mTest->runTest();
#endif

	//testApi();

	//GCtx->setUiMgr(new UIManager());
	//GCtx->setEngineApi(new EngineApi());
	//GCtx->setNetMgr(new NetMgr(Ctx::getSingletonPtr()->getStdLog()));

	// test
	//GUiMgr->loadForm(eUIPack);
	//GNetMgr->openSocket("192.168.124.26", 10002);
}

void Ctx::setUiMgr(UIMgr* uiMgr)
{
	this->mUiMgr = uiMgr;
}

UIMgr* Ctx::getUIMgr()
{
	return this->mUiMgr;
}

EngineData* Ctx::getEngineData()
{
	return this->mEngineData;
}

void Ctx::setNetMgr(INetMgr* pINetMgr)
{
	this->mNetMgr = pINetMgr;
}

INetMgr* Ctx::getNetMgr()
{
	return this->mNetMgr;
}

#ifdef USE_EXTERN_THREAD
StdoutLog* Ctx::getStdLog()
{
	return this->mStdoutLog;
}
#endif

TableSys* Ctx::getTableSys()
{
	return this->mTableSys;
}

LogSys* Ctx::getLogSys()
{
	return this->mLogSys;
}

ShareData* Ctx::getShareData()
{
	return this->mShareData;
}

NetDispList* Ctx::getNetDispList()
{
	return this->mNetDispList;
}

Config* Ctx::getConfig()
{
	return this->mConfig;
}

LocalFileSys* Ctx::getLocalFileSys()
{
	return this->mLocalFileSys;
}

PoolSys* Ctx::getPoolSys()
{
	return this->mPoolSys;
}

UIAssetMgr* Ctx::getUiAssetMgr()
{
	return this->mUiAssetMgr;
}

ResLoadMgr* Ctx::getResLoadMgr()
{
	return this->mResLoadMgr;
}

FSandboxPlatformFile* Ctx::getSandboxPlatformFile()
{
	return this->mSandboxPlatformFile;
}

FMyStreamableManager* Ctx::getMyStreamableManager()
{
	return this->mMyStreamableManager;
}

void Ctx::testApi()
{
	EngineApi::GameUserDir();
}