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
#include "MFileSys.h"
#include "PoolSys.h"

#include "ResLoadMgr.h"
#include "ClassAssetInsMgr.h"
#include "ObjectAssetInsMgr.h"
#include "MyStreamableManager.h"
#include "DownloadMgr.h"
#include "SystemSetting.h"
#include "LuaSystem.h"
#include "GameSceneEventCB.h"
#include "MyLatentActionManager.h"

#include "SceneSys.h"
#include "SystemTimeData.h"
#include "SystemFrameData.h"
#include "ProcessSys.h"
#include "EngineLoop.h"
#include "DelayTaskMgr.h"

#include "TickMgr.h"
#include "TimerMgr.h"
#include "FrameTimerMgr.h"
#include "TickPriority.h"

// 偏特化
template<> Ctx* Ctx::Singleton<Ctx>::msSingleton = 0;

Ctx::Ctx()
{
	this->mIsInit = false;
	this->mUiMgr = nullptr;
	this->mEngineData = nullptr;
	this->mNetMgr = nullptr;
	this->mTableSys = nullptr;

#ifdef USE_EXTERN_THREAD
	this->mStdoutLog = nullptr;
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

	this->mSystemSetting = nullptr;
	this->mLuaSystem = nullptr;
	this->mSceneEventCB = nullptr;
	this->mMyLatentActionManager = nullptr;

	this->mSceneSys = nullptr;
	this->mSystemTimeData = nullptr;
	this->mSystemFrameData = nullptr;
	this->mProcessSys = nullptr;
	this->mEngineLoop = nullptr;
	this->mDelayTaskMgr = nullptr;

	this->mTickMgr = nullptr;
	this->mTimerMgr = nullptr;
	this->mFrameTimerMgr = nullptr;
}

Ctx::~Ctx()
{
	this->dispose();
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
	this->mSystemSetting = MySharedPtr<SystemSetting>(SAFE_NEW SystemSetting());
	this->mLuaSystem = MySharedPtr<LuaSystem>(SAFE_NEW LuaSystem());
	this->mSceneEventCB = MySharedPtr<ISceneEventCB>(SAFE_NEW GameSceneEventCB());
	this->mMyLatentActionManager = MySharedPtr<MyLatentActionManager>(SAFE_NEW MyLatentActionManager());

	this->mSceneSys = MySharedPtr<SceneSys>(SAFE_NEW SceneSys());
	this->mSystemTimeData = MySharedPtr<SystemTimeData>(SAFE_NEW SystemTimeData());
	this->mSystemFrameData = MySharedPtr<SystemFrameData>(SAFE_NEW SystemFrameData());
	this->mProcessSys = MySharedPtr<ProcessSys>(SAFE_NEW ProcessSys());
	this->mEngineLoop = MySharedPtr<EngineLoop>(SAFE_NEW EngineLoop());
	this->mDelayTaskMgr = MySharedPtr<DelayTaskMgr>(SAFE_NEW DelayTaskMgr());

	this->mTickMgr = MySharedPtr<TickMgr>(SAFE_NEW TickMgr());
	this->mTimerMgr = MySharedPtr<TimerMgr>(SAFE_NEW TimerMgr());
	this->mFrameTimerMgr = MySharedPtr<FrameTimerMgr>(SAFE_NEW FrameTimerMgr());
}

void Ctx::init()
{
	this->mIsInit = true;
	this->mMyStreamableManager->init();
	this->mUiMgr->init();
	this->mResLoadMgr->init();
	this->mClassAssetInsMgr->init();
	this->mObjectAssetInsMgr->init();
	this->mPoolSys->init();
	this->mDownloadMgr->init();
	this->mFileSys->init();
	this->mSystemSetting->init();
	this->mLuaSystem->init();
	this->mSceneEventCB->init();
	this->mMyLatentActionManager->init();

	this->mSceneSys->init();
	this->mSystemTimeData->init();
	this->mSystemFrameData->init();
	this->mProcessSys->init();
	this->mEngineLoop->init();
	this->mDelayTaskMgr->init();

	this->mTickMgr->init();
	this->mTimerMgr->init();
	this->mFrameTimerMgr->init();

	this->addEventHandle();

	// 挂在目录
	EngineApi::InsertMountPoint("/CacheData/", "E:/Self/Self/unreal/UE-GIT/UE-BP");
}

void Ctx::dispose()
{
	this->mIsInit = false;

	this->mUiMgr->dispose();
	this->mEngineData->dispose();
	this->mNetMgr->dispose();
	this->mTableSys->dispose();

	this->mLogSys->dispose();
	this->mNetDispList->dispose();
	this->mShareData->dispose();
	this->mConfig->dispose();

	this->mResLoadMgr->dispose();
	this->mClassAssetInsMgr->dispose();
	this->mObjectAssetInsMgr->dispose();

	this->mMyStreamableManager->dispose();
	this->mPoolSys->dispose();
	this->mFileSys->dispose();

	this->mSystemSetting->dispose();
	this->mLuaSystem->dispose();
	this->mSceneEventCB->dispose();
	this->mMyLatentActionManager->dispose();

	this->mSceneSys->dispose();
	this->mSystemTimeData->dispose();
	this->mSystemFrameData->dispose();
	this->mProcessSys->dispose();
	this->mEngineLoop->dispose();
	this->mDelayTaskMgr->dispose();

	this->mTickMgr->dispose();
	this->mTimerMgr->dispose();
	this->mFrameTimerMgr->dispose();

	this->mUiMgr = nullptr;
	this->mEngineData = nullptr;
	this->mNetMgr = nullptr;
	this->mTableSys = nullptr;

#ifdef USE_EXTERN_THREAD
	this->mStdoutLog = nullptr;
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

	this->mSystemSetting = nullptr;
	this->mLuaSystem = nullptr;
	this->mSceneEventCB = nullptr;
	this->mMyLatentActionManager = nullptr;

	this->mSceneSys = nullptr;
	this->mSystemTimeData = nullptr;
	this->mSystemFrameData = nullptr;
	this->mProcessSys = nullptr;
	this->mEngineLoop = nullptr;
	this->mDelayTaskMgr = nullptr;

	this->mTickMgr = nullptr;
	this->mTimerMgr = nullptr;
	this->mFrameTimerMgr = nullptr;
}

void Ctx::beginPlay()
{
	if (!this->mIsInit)
	{
		this->init();
		this->mSceneEventCB->onLevelLoaded();

		//testApi();

		//GCtx->setUiMgr(new UIManager());
		//GCtx->setEngineApi(new EngineApi());
		//GCtx->setNetMgr(new NetMgr(Ctx::getSingletonPtr()->getStdLog()));

		// test
		//GUiMgr->loadForm(eUIPack);
		//GNetMgr->openSocket("192.168.124.26", 10002);
	}
}

void Ctx::mainLoop()
{
	if (this->mIsInit)
	{
		GEngineLoop->MainLoop();
	}
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

MySharedPtr<SystemSetting> Ctx::getSystemSetting()
{
	return mSystemSetting;
}

MySharedPtr<LuaSystem> Ctx::getLuaSystem()
{
	return mLuaSystem;
}

MySharedPtr<ISceneEventCB> Ctx::getSceneEventCB()
{
	return mSceneEventCB;
}

MySharedPtr<MyLatentActionManager> Ctx::getMyLatentActionManager()
{
	return mMyLatentActionManager;
}

MySharedPtr<SceneSys> Ctx::getSceneSys()
{
	return mSceneSys;
}

MySharedPtr<SystemTimeData> Ctx::getSystemTimeData()
{
	return mSystemTimeData;
}

MySharedPtr<SystemFrameData> Ctx::getSystemFrameData()
{
	return mSystemFrameData;
}

MySharedPtr<ProcessSys> Ctx::getProcessSys()
{
	return mProcessSys;
}

MySharedPtr<EngineLoop> Ctx::getEngineLoop()
{
	return mEngineLoop;
}

MySharedPtr<DelayTaskMgr> Ctx::getDelayTaskMgr()
{
	return mDelayTaskMgr;
}

MySharedPtr<TickMgr> Ctx::getTickMgr()
{
	return mTickMgr;
}

MySharedPtr<TimerMgr> Ctx::getTimerMgr()
{
	return mTimerMgr;
}

MySharedPtr<FrameTimerMgr> Ctx::getFrameTimerMgr()
{
	return mFrameTimerMgr;
}

void Ctx::addEventHandle()
{
	this->mTickMgr->addTick(this->mDelayTaskMgr, TickPriority::eTPDelayTaskMgr);
}

void Ctx::testApi()
{
	EngineApi::GameUserDir();
}