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
#include "MFileSys.h"
#include "PoolSys.h"

#include "ResLoadMgr.h"
#include "ClassAssetInsMgr.h"
#include "ObjectAssetInsMgr.h"
#include "MyStreamableManager.h"
#include "DownloadMgr.h"

#include "Ctx.h"

#ifdef ENABLE_UNIT_TEST
	#include "TestMain.h"
#endif

// 偏特化
template<> Ctx* Ctx::Singleton<Ctx>::msSingleton = 0;

Ctx::Ctx()
{
	
}

Ctx::~Ctx()
{
	this->mUiMgr = nullptr;
	this->mEngineData = nullptr;
	this->mNetMgr = nullptr;
	this->mTableSys = nullptr;

#ifdef USE_EXTERN_THREAD
	this->mStdoutLog = nullptr;
#endif

#ifdef ENABLE_UNIT_TEST
	this->mTestMain = nullptr;
#endif

	this->mLogSys = nullptr;
	this->mNetDispList = nullptr;
	this->mShareData = nullptr;
	this->mConfig = nullptr;

	this->mResLoadMgr = nullptr;
	this->mClassAssetInsMgr = nullptr;
	this->mObjectAssetInsMgr = nullptr;

	this->mMyStreamableManager = nullptr;
	this->mPoolSys = nullptr;
	this->mFileSys = nullptr;
}

void Ctx::construct()
{
	this->mShareData = MySharedPtr<ShareData>(SAFE_NEW ShareData());
	this->mNetDispList = MySharedPtr<NetDispList>(SAFE_NEW NetDispList());
	this->mLogSys = MySharedPtr<LogSys>(SAFE_NEW LogSys());
	this->mEngineData = MySharedPtr<EngineData>(SAFE_NEW EngineData());

#ifdef USE_EXTERN_THREAD
	this->mStdoutLog = MySharedPtr<StdoutLog>(SAFE_NEW StdoutLog());
#endif

	this->mMyStreamableManager = MySharedPtr<FMyStreamableManager>(SAFE_NEW FMyStreamableManager());
	this->mResLoadMgr = MySharedPtr<ResLoadMgr>(SAFE_NEW ResLoadMgr());
	this->mClassAssetInsMgr = MySharedPtr<ClassAssetInsMgr>(SAFE_NEW ClassAssetInsMgr());
	this->mObjectAssetInsMgr = MySharedPtr<ObjectAssetInsMgr>(SAFE_NEW ObjectAssetInsMgr());

	this->mUiMgr = MySharedPtr<UIMgr>(SAFE_NEW UIMgr());
	this->mTableSys = MySharedPtr<TableSys>(SAFE_NEW TableSys());
	this->mConfig = MySharedPtr<Config>(SAFE_NEW Config());

#ifdef	USE_EXTERN_THREAD
	this->mNetMgr = MySharedPtr<NetMgr>(SAFE_NEW NetMgr(getStdLog());
#else
	this->mNetMgr = MySharedPtr<NetMgr>(SAFE_NEW NetMgr());
#endif

	this->mPoolSys = MySharedPtr<PoolSys>(SAFE_NEW PoolSys());
	this->mDownloadMgr = MySharedPtr<DownloadMgr>(SAFE_NEW DownloadMgr());
	this->mFileSys = MySharedPtr<MFileSys>(SAFE_NEW MFileSys());
}

void Ctx::init()
{
	this->mMyStreamableManager->init();
	this->mUiMgr->init();
	this->mResLoadMgr->init();
	this->mClassAssetInsMgr->init();
	this->mObjectAssetInsMgr->init();
	this->mPoolSys->init();
	this->mDownloadMgr->init();
	this->mFileSys->init();

	// 挂在目录
	EngineApi::InsertMountPoint("/CacheData/", "E:/Self/Self/unreal/UE-GIT/UE-BP");
}

void Ctx::beginPlay()
{
	this->init();

#ifdef ENABLE_UNIT_TEST
	this->mTestMain = MySharedPtr<TestMain>(new TestMain());
	this->mTestMain->runTest();
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
	this->mUiMgr.reset(uiMgr);
}

MySharedPtr<UIMgr> Ctx::getUIMgr()
{
	return this->mUiMgr;
}

MySharedPtr<EngineData> Ctx::getEngineData()
{
	return this->mEngineData;
}

void Ctx::setNetMgr(INetMgr* pINetMgr)
{
	this->mNetMgr.reset(pINetMgr);
}

MySharedPtr<INetMgr> Ctx::getNetMgr()
{
	return this->mNetMgr;
}

#ifdef USE_EXTERN_THREAD
MySharedPtr<StdoutLog> Ctx::getStdLog()
{
	return this->mStdoutLog;
}
#endif

MySharedPtr<TableSys> Ctx::getTableSys()
{
	return this->mTableSys;
}

MySharedPtr<LogSys> Ctx::getLogSys()
{
	return this->mLogSys;
}

MySharedPtr<ShareData> Ctx::getShareData()
{
	return this->mShareData;
}

MySharedPtr<NetDispList> Ctx::getNetDispList()
{
	return this->mNetDispList;
}

MySharedPtr<Config> Ctx::getConfig()
{
	return this->mConfig;
}

MySharedPtr<LocalFileSys> Ctx::getLocalFileSys()
{
	return this->mLocalFileSys;
}

MySharedPtr<PoolSys> Ctx::getPoolSys()
{
	return this->mPoolSys;
}

MySharedPtr<ClassAssetInsMgr> Ctx::getClassAssetInsMgr()
{
	return this->mClassAssetInsMgr;
}

MySharedPtr<ObjectAssetInsMgr> Ctx::getObjectAssetInsMgr()
{
	return this->mObjectAssetInsMgr;
}

MySharedPtr<ResLoadMgr> Ctx::getResLoadMgr()
{
	return this->mResLoadMgr;
}

MySharedPtr<FMyStreamableManager> Ctx::getMyStreamableManager()
{
	return this->mMyStreamableManager;
}

MySharedPtr<DownloadMgr> Ctx::getDownloadMgr()
{
	return this->mDownloadMgr;
}

MySharedPtr<MFileSys> Ctx::getFileSys()
{
	return this->mFileSys;
}

void Ctx::testApi()
{
	EngineApi::GameUserDir();
}