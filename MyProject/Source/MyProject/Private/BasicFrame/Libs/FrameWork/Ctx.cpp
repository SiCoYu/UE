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
	delete this->mUiMgr;
	delete this->mEngineData;
	delete this->mNetMgr;
	delete this->mTableSys;

#ifdef USE_EXTERN_THREAD
	delete this->mStdoutLog;
#endif

#ifdef ENABLE_UNIT_TEST
	delete this->mTestMain;
#endif

	delete this->mLogSys;
	delete this->mNetDispList;
	delete this->mShareData;
	delete this->mConfig;

	delete this->mResLoadMgr;
	delete this->mClassAssetInsMgr;
	delete this->mObjectAssetInsMgr;

	delete this->mMyStreamableManager;
	delete this->mPoolSys;
	delete this->mFileSys;
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

	this->mMyStreamableManager = new FMyStreamableManager();
	this->mResLoadMgr = new ResLoadMgr();
	this->mClassAssetInsMgr = new ClassAssetInsMgr();
	this->mObjectAssetInsMgr = new ObjectAssetInsMgr();

	this->mUiMgr = new UIMgr();
	this->mTableSys = new TableSys();
	this->mConfig = new Config();

#ifdef	USE_EXTERN_THREAD
	this->mNetMgr = new NetMgr(getStdLog());
#else
	this->mNetMgr = new NetMgr();
#endif

	this->mPoolSys = new PoolSys();
	this->mDownloadMgr = new DownloadMgr();
	this->mFileSys = new MFileSys();
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
	this->mTestMain = new TestMain();
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

ClassAssetInsMgr* Ctx::getClassAssetInsMgr()
{
	return this->mClassAssetInsMgr;
}

ObjectAssetInsMgr* Ctx::getObjectAssetInsMgr()
{
	return this->mObjectAssetInsMgr;
}

ResLoadMgr* Ctx::getResLoadMgr()
{
	return this->mResLoadMgr;
}

FMyStreamableManager* Ctx::getMyStreamableManager()
{
	return this->mMyStreamableManager;
}

DownloadMgr* Ctx::getDownloadMgr()
{
	return this->mDownloadMgr;
}

MFileSys* Ctx::getFileSys()
{
	return this->mFileSys;
}

void Ctx::testApi()
{
	EngineApi::GameUserDir();
}