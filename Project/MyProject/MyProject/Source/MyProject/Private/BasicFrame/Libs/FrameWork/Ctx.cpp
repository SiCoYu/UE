#include "MyProject.h"
#include "Ctx.h"

#include "EngineData.h"
#include "INetMgr.h"
#include "UiMgr.h"
#include "NetMgr.h"
#include "UtilEngineWrap.h"
#include "TableSys.h"
#include "ShareData.h"
#include "NetCmdNotify.h"
#include "LogSys.h"
#include "Config.h"
#include "MFileSys.h"
#include "PoolSys.h"

#include "ResLoadMgr.h"
#include "ClassAssetInsMgr.h"
#include "ObjectAssetInsMgr.h"
#include "TextureInsResMgr.h"
#include "MaterialInsResMgr.h"
#include "MyStreamableManager.h"
#include "DownloadMgr.h"
#include "SystemSetting.h"
#include "LuaSystem.h"
#include "GameSceneEventNotify.h"
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
//#include "MySingletonBP.h"
#include "MyBluePrintBase.h"
#include "MyMemoryTracker.h"
#include "MyNativeObjectReferencer.h"

// 偏特化
template<> Ctx* Ctx::Singleton<Ctx>::msSingleton = 0;

Ctx::Ctx()
{
	this->mIsInit = false;
	this->mUiMgr.setNull();
	this->mEngineData.setNull();
	this->mNetMgr.setNull();
	this->mTableSys.setNull();

#ifdef USE_EXTERN_THREAD
	this->mStdoutLog.setNull();
#endif

	this->mLogSys.setNull();
	this->mNetDispatchList.setNull();
	this->mShareData.setNull();
	this->mConfig.setNull();

	this->mResLoadMgr.setNull();
	this->mClassAssetInsMgr.setNull();
	this->mObjectAssetInsMgr.setNull();
	this->mTextureInsResMgr.setNull();
	this->mMaterialInsResMgr.setNull();

	this->mMyStreamableManager.setNull();
	this->mPoolSys.setNull();
	this->mFileSys.setNull();

	this->mSystemSetting.setNull();
	this->mLuaSystem.setNull();
	this->mSceneEventNotify.setNull();
	this->mMyLatentActionManager.setNull();

	this->mSceneSys.setNull();
	this->mSystemTimeData.setNull();
	this->mSystemFrameData.setNull();
	this->mProcessSys.setNull();
	this->mEngineLoop.setNull();
	this->mDelayTaskMgr.setNull();

	this->mTickMgr.setNull();
	this->mTimerMgr.setNull();
	this->mFrameTimerMgr.setNull();

	this->mBPCtx = nullptr;
	this->mMyNativeObjectReferencer = nullptr;
}

Ctx::~Ctx()
{
	//this->dispose();
}

void Ctx::construct()
{
	this->mShareData = MySharedPtr<ShareData>(MY_NEW ShareData());
	this->mNetDispatchList = MySharedPtr<NetCmdNotify>(MY_NEW NetCmdNotify());
	this->mLogSys = MySharedPtr<LogSys>(MY_NEW LogSys());
	this->mEngineData = MySharedPtr<EngineData>(MY_NEW EngineData());

#ifdef USE_EXTERN_THREAD
	this->mStdoutLog = MySharedPtr<StdoutLog>(MY_NEW StdoutLog());
#endif

	this->mMyStreamableManager = MySharedPtr<MyStreamableManager>(MY_NEW MyStreamableManager());
	this->mResLoadMgr = MySharedPtr<ResLoadMgr>(MY_NEW ResLoadMgr());
	this->mClassAssetInsMgr = MySharedPtr<ClassAssetInsMgr>(MY_NEW ClassAssetInsMgr());
	this->mObjectAssetInsMgr = MySharedPtr<ObjectAssetInsMgr>(MY_NEW ObjectAssetInsMgr());
	this->mTextureInsResMgr = MySharedPtr<TextureInsResMgr>(MY_NEW TextureInsResMgr());
	this->mMaterialInsResMgr = MySharedPtr<MaterialInsResMgr>(MY_NEW MaterialInsResMgr());

	this->mUiMgr = MySharedPtr<UiMgr>(MY_NEW UiMgr());
	this->mTableSys = MySharedPtr<TableSys>(MY_NEW TableSys());
	this->mConfig = MySharedPtr<Config>(MY_NEW Config());

#ifdef	USE_EXTERN_THREAD
	this->mNetMgr = MySharedPtr<NetMgr>(MY_NEW NetMgr(getStdLog());
#else
	this->mNetMgr = MySharedPtr<NetMgr>(MY_NEW NetMgr());
#endif

	this->mPoolSys = MySharedPtr<PoolSys>(MY_NEW PoolSys());
	this->mDownloadMgr = MySharedPtr<DownloadMgr>(MY_NEW DownloadMgr());
	this->mFileSys = MySharedPtr<MFileSys>(MY_NEW MFileSys());
	this->mSystemSetting = MySharedPtr<SystemSetting>(MY_NEW SystemSetting());
	this->mLuaSystem = MySharedPtr<LuaSystem>(MY_NEW LuaSystem());
	this->mSceneEventNotify = MySharedPtr<ISceneEventNotify>(MY_NEW GameSceneEventNotify());
	this->mMyLatentActionManager = MySharedPtr<MyLatentActionManager>(MY_NEW MyLatentActionManager());

	this->mSceneSys = MySharedPtr<SceneSys>(MY_NEW SceneSys());
	this->mSystemTimeData = MySharedPtr<SystemTimeData>(MY_NEW SystemTimeData());
	this->mSystemFrameData = MySharedPtr<SystemFrameData>(MY_NEW SystemFrameData());
	this->mProcessSys = MySharedPtr<ProcessSys>(MY_NEW ProcessSys());
	this->mEngineLoop = MySharedPtr<EngineLoop>(MY_NEW EngineLoop());
	this->mDelayTaskMgr = MySharedPtr<DelayTaskMgr>(MY_NEW DelayTaskMgr());

	this->mTickMgr = MySharedPtr<TickMgr>(MY_NEW TickMgr());
	this->mTimerMgr = MySharedPtr<TimerMgr>(MY_NEW TimerMgr());
	this->mFrameTimerMgr = MySharedPtr<FrameTimerMgr>(MY_NEW FrameTimerMgr());

	this->mMyNativeObjectReferencer = new FMyNativeObjectReferencer();

	// 最后初始化 BluePrint 数据
	// 这个时候还没有获取 GEngineData->getMainActor() ，使用会报错
	//UClass *bpCtxClass = LoadClass<UObject>(NULL, TEXT("/Game/MyAsset/MyBlueprints/Lib/FrameWork/Ctx.Ctx_C"), NULL, LOAD_None, NULL);
	//UGameInstance* pGameIns = (UGameInstance*)UtilEngineWrap::GetGameInstance();
	//this->mBPCtx = MySharedPtr<UMyBluePrintBase>(::NewObject<UMyBluePrintBase>(pGameIns, bpCtxClass, FName("UMySingletonBP")));
	//FString cmd = TEXT("init");
	//FOutputDeviceDebug device;
	//this->mBPCtx->CallFunctionByNameWithArguments(*cmd, device, NULL, true);
}

void Ctx::init()
{
	this->mIsInit = true;
	this->mMyStreamableManager->init();
	this->mUiMgr->init();
	this->mResLoadMgr->init();
	this->mClassAssetInsMgr->init();
	this->mObjectAssetInsMgr->init();
	this->mTextureInsResMgr->init();
	this->mMaterialInsResMgr->init();
	this->mPoolSys->init();
	this->mDownloadMgr->init();
	this->mFileSys->init();
	this->mSystemSetting->init();
	this->mLuaSystem->init();
	this->mSceneEventNotify->init();
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

	this->mBPCtx->init();
	this->mMyNativeObjectReferencer->init();

	this->addEventHandle();

	// 挂在目录
	UtilEngineWrap::InsertMountPoint("/CacheData/", "E:/Self/Self/unreal/UE-GIT/UE-BP");
}

void Ctx::dispose()
{
	this->mIsInit = false;

	this->mUiMgr->dispose();
	this->mEngineData->dispose();
	this->mNetMgr->dispose();
	this->mTableSys->dispose();

	this->mLogSys->dispose();
	this->mNetDispatchList->dispose();
	this->mShareData->dispose();
	this->mConfig->dispose();

	this->mResLoadMgr->dispose();
	this->mClassAssetInsMgr->dispose();
	this->mObjectAssetInsMgr->dispose();
	this->mTextureInsResMgr->dispose();
	this->mMaterialInsResMgr->dispose();

	this->mMyStreamableManager->dispose();
	this->mDownloadMgr->dispose();
	this->mPoolSys->dispose();
	this->mFileSys->dispose();

	this->mSystemSetting->dispose();
	this->mLuaSystem->dispose();
	this->mSceneEventNotify->dispose();
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

	this->mBPCtx->dispose();
	this->mMyNativeObjectReferencer->dispose();

	this->mUiMgr.setNull();
	this->mEngineData.setNull();

	// INetMgr 不继承 GObject ，不能运行自己的 delete 
	MY_DELETE (GObject*)this->mNetMgr.getPointer();
	this->mNetMgr.reset(0);
	this->mNetMgr.setNull();

	this->mTableSys.setNull();

#ifdef USE_EXTERN_THREAD
	this->mStdoutLog.setNull();
#endif

	this->mLogSys.setNull();
	this->mNetDispatchList.setNull();
	this->mShareData.setNull();
	this->mConfig.setNull();

	this->mResLoadMgr.setNull();
	this->mClassAssetInsMgr.setNull();
	this->mObjectAssetInsMgr.setNull();
	this->mTextureInsResMgr.setNull();
	this->mMaterialInsResMgr.setNull();

	this->mMyStreamableManager.setNull();
	this->mDownloadMgr.setNull();
	this->mPoolSys.setNull();
	this->mFileSys.setNull();

	this->mSystemSetting.setNull();
	this->mLuaSystem.setNull();
	this->mSceneEventNotify.setNull();
	this->mMyLatentActionManager.setNull();

	this->mSceneSys.setNull();
	this->mSystemTimeData.setNull();
	this->mSystemFrameData.setNull();
	this->mProcessSys.setNull();
	this->mEngineLoop.setNull();
	this->mDelayTaskMgr.setNull();

	this->mTickMgr.setNull();
	this->mTimerMgr.setNull();
	this->mFrameTimerMgr.setNull();
	this->mBPCtx = nullptr;

	// 静态全局变量的清理工作
	MyMemoryTracker::get().reportLeaks();
	MyMemoryTracker::get().clear();

	// 清除类库
	MClassFactory::Destroy();
}

void Ctx::beginPlay()
{
	if (!this->mIsInit)
	{
		this->init();
		this->mSceneEventNotify->onLevelLoaded();

		//testApi();

		//GCtx->setUiMgr(new UIManager());
		//GCtx->setEngineApi(new UtilEngineWrap());
		//GCtx->setNetMgr(new NetMgr(Ctx::getSingletonPtr()->getStdLog()));

		// test
		//GUiMgr->loadForm(eUiPack);
		//GNetMgr->openSocket("192.168.124.26", 10002);

		//FString cmd = FString::Printf(TEXT("GlobalEventCmd onInit"));
		//FOutputDeviceDebug device;
		//this->mEngineData->getMainActor()->CallFunctionByNameWithArguments(*cmd, device, NULL, true);

		// 初始化 BP
		//UMySingletonBP::getSingleton()->init();

		// 最后初始化 BluePrint 数据
		UClass *bpCtxClass = LoadClass<UObject>(NULL, TEXT("/Game/MyAsset/MyBlueprints/Lib/FrameWork/Ctx.Ctx_C"), NULL, LOAD_None, NULL);
		UGameInstance* pGameIns = (UGameInstance*)UtilEngineWrap::GetGameInstance();
		this->mBPCtx = ::NewObject<UMyBluePrintBase>(pGameIns, bpCtxClass, FName("UMyBluePrintBase"));
		FString cmd = TEXT("init");
		FOutputDeviceDebug device;
		this->mBPCtx->CallFunctionByNameWithArguments(*cmd, device, NULL, true);
	}
}

void Ctx::mainLoop()
{
	if (this->mIsInit)
	{
		GEngineLoop->MainLoop();
	}
}

void Ctx::setUiMgr(UiMgr* uiMgr)
{
	this->mUiMgr.reset(uiMgr);
}

MySharedPtr<UiMgr> Ctx::getUIMgr()
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

MySharedPtr<NetCmdNotify> Ctx::getNetDispatchList()
{
	return this->mNetDispatchList;
}

MySharedPtr<Config> Ctx::getConfig()
{
	return this->mConfig;
}

//MySharedPtr<LocalFileSys> Ctx::getLocalFileSys()
//{
//	return this->mLocalFileSys;
//}

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

MySharedPtr<TextureInsResMgr> Ctx::getTextureInsResMgr()
{
	return this->mTextureInsResMgr;
}

MySharedPtr<MaterialInsResMgr> Ctx::getMaterialInsResMgr()
{
	return this->mMaterialInsResMgr;
}

MySharedPtr<ResLoadMgr> Ctx::getResLoadMgr()
{
	return this->mResLoadMgr;
}

MySharedPtr<MyStreamableManager> Ctx::getMyStreamableManager()
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
	return this->mSystemSetting;
}

MySharedPtr<LuaSystem> Ctx::getLuaSystem()
{
	return this->mLuaSystem;
}

MySharedPtr<ISceneEventNotify> Ctx::getSceneEventCB()
{
	return this->mSceneEventNotify;
}

MySharedPtr<MyLatentActionManager> Ctx::getMyLatentActionManager()
{
	return this->mMyLatentActionManager;
}

MySharedPtr<SceneSys> Ctx::getSceneSys()
{
	return this->mSceneSys;
}

MySharedPtr<SystemTimeData> Ctx::getSystemTimeData()
{
	return this->mSystemTimeData;
}

MySharedPtr<SystemFrameData> Ctx::getSystemFrameData()
{
	return mSystemFrameData;
}

MySharedPtr<ProcessSys> Ctx::getProcessSys()
{
	return this->mProcessSys;
}

MySharedPtr<EngineLoop> Ctx::getEngineLoop()
{
	return this->mEngineLoop;
}

MySharedPtr<DelayTaskMgr> Ctx::getDelayTaskMgr()
{
	return this->mDelayTaskMgr;
}

MySharedPtr<TickMgr> Ctx::getTickMgr()
{
	return this->mTickMgr;
}

MySharedPtr<TimerMgr> Ctx::getTimerMgr()
{
	return this->mTimerMgr;
}

MySharedPtr<FrameTimerMgr> Ctx::getFrameTimerMgr()
{
	return this->mFrameTimerMgr;
}

UMyBluePrintBase* Ctx::getBPCtx()
{
	return this->mBPCtx;
}

FMyNativeObjectReferencer* Ctx::getNativeObjectReferencer()
{
	return this->mMyNativeObjectReferencer;
}

void Ctx::addEventHandle()
{
	this->mTickMgr->addTick(this->mDelayTaskMgr.get(), TickPriority::eTPDelayTaskMgr);
}

void Ctx::testApi()
{
	UtilEngineWrap::GameUserDir();
}