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
#include "PlatformDefine.h"

// 类的声明和定义一定要完全一样，包括 namespace
MY_BEGIN_NAMESPACE(MyNS)

class UiMgr;
class INetMgr;
class TableSys;
class ShareData;
class NetCmdNotify;
class Config;
//class LocalFileSys;
class PoolSys;

class ResLoadMgr;
class ClassAssetInsMgr;
class ObjectAssetInsMgr;
class TextureInsResMgr;
class MaterialInsResMgr;
class MyStreamableManager;
class DownloadMgr;
class MFileSys;
class SystemSetting;

class SceneSys;
class SystemTimeData;
class SystemFrameData;
class ProcessSys;
class EngineLoop;
class DelayTaskMgr;

class TickMgr;
class TimerMgr;
class FrameTimerMgr;

class EngineData;
class LogSys;
class LuaSystem;
class MyLatentActionManager;
class GObject;
class InputMgr;
class MsgRouteNotify;
class GlobalDelegate;
class GlobalEventCmd;

MY_END_NAMESPACE

class FMyNativeObjectReferencer;

class UMyBluePrintBase;
class UGameInstance;

MY_BEGIN_NAMESPACE(MyNS)

class Ctx : public Singleton<Ctx>
{
protected:
	bool mIsInit;

	MySharedPtr<UiMgr> mUiMgr;
	MySharedPtr<EngineData> mEngineData;
	MySharedPtr<INetMgr> mNetMgr;		// INetMgr 不是继承 GObject ，不能运行自己重载删除 delete 接口
	MySharedPtr<TableSys> mTableSys;
	MySharedPtr<LogSys> mLogSys;
	MySharedPtr<ShareData> mShareData;
	MySharedPtr<NetCmdNotify> mNetCmdNotify;
	MySharedPtr<Config> mConfig;
	//MySharedPtr<LocalFileSys> mLocalFileSys;
	MySharedPtr<PoolSys> mPoolSys;
	MySharedPtr<ResLoadMgr> mResLoadMgr;
	MySharedPtr<ClassAssetInsMgr> mClassAssetInsMgr;
	MySharedPtr<ObjectAssetInsMgr> mObjectAssetInsMgr;
	MySharedPtr<TextureInsResMgr> mTextureInsResMgr;
	MySharedPtr<MaterialInsResMgr> mMaterialInsResMgr;

	MySharedPtr<MyStreamableManager> mMyStreamableManager;
	MySharedPtr<DownloadMgr> mDownloadMgr;
	MySharedPtr<MFileSys> mFileSys;
	MySharedPtr<SystemSetting> mSystemSetting;
	MySharedPtr<LuaSystem> mLuaSystem;
	MySharedPtr<MyLatentActionManager> mMyLatentActionManager;

	MySharedPtr<SceneSys> mSceneSys;
	MySharedPtr<SystemTimeData> mSystemTimeData;
	MySharedPtr<SystemFrameData> mSystemFrameData;
	MySharedPtr<ProcessSys> mProcessSys;
	MySharedPtr<EngineLoop> mEngineLoop;
	MySharedPtr<DelayTaskMgr> mDelayTaskMgr;

	MySharedPtr<TickMgr> mTickMgr;
	MySharedPtr<TimerMgr> mTimerMgr;
	MySharedPtr<FrameTimerMgr> mFrameTimerMgr;
	MySharedPtr<InputMgr> mInputMgr;
	MySharedPtr<MsgRouteNotify> mMsgRouteNotify;
	MySharedPtr<GlobalDelegate> mGlobalDelegate;
	MySharedPtr<GlobalEventCmd> mGlobalEventCmd;
	//MySharedPtr<UMyBluePrintBase> mBPCtx;

	UMyBluePrintBase* mBPCtx;
	FMyNativeObjectReferencer* mMyNativeObjectReferencer;

#ifdef USE_EXTERN_THREAD
	MySharedPtr<StdoutLog*> mStdoutLog;
#endif

protected:
	void _preInit();
	void _execInit();
	void _postInit();

	void _preDispose();
	void _execDispose();
	void _postDispose();

public:
	Ctx();
	virtual ~Ctx();

	virtual void construct();
	virtual void init();
	virtual void dispose();

	void beginPlay();
	void mainLoop();
	void addEventHandle();

	void setUiMgr(UiMgr* uiMgr);
	MySharedPtr<UiMgr> getUIMgr();

	MySharedPtr<EngineData> getEngineData();
	void setNetMgr(INetMgr* pINetMgr);
	MySharedPtr<INetMgr> getNetMgr();
	MySharedPtr<TableSys> getTableSys();
	MySharedPtr<LogSys> getLogSys();
	MySharedPtr<ShareData> getShareData();
	MySharedPtr<NetCmdNotify> getNetCmdNotify();
	MySharedPtr<Config> getConfig();
	//MySharedPtr<LocalFileSys> getLocalFileSys();
	MySharedPtr<PoolSys> getPoolSys();
	MySharedPtr<ResLoadMgr> getResLoadMgr();

	MySharedPtr<ClassAssetInsMgr> getClassAssetInsMgr();
	MySharedPtr<ObjectAssetInsMgr> getObjectAssetInsMgr();
	MySharedPtr<TextureInsResMgr> getTextureInsResMgr();
	MySharedPtr<MaterialInsResMgr> getMaterialInsResMgr();

	MySharedPtr<MyStreamableManager> getMyStreamableManager();
	MySharedPtr<DownloadMgr> getDownloadMgr();
	MySharedPtr<MFileSys> getFileSys();
	MySharedPtr<SystemSetting> getSystemSetting();
	MySharedPtr<LuaSystem> getLuaSystem();
	MySharedPtr<MyLatentActionManager> getMyLatentActionManager();

	MySharedPtr<SceneSys> getSceneSys();
	MySharedPtr<SystemTimeData> getSystemTimeData();
	MySharedPtr<SystemFrameData> getSystemFrameData();
	MySharedPtr<ProcessSys> getProcessSys();
	MySharedPtr<EngineLoop> getEngineLoop();
	MySharedPtr<DelayTaskMgr> getDelayTaskMgr();

	MySharedPtr<TickMgr> getTickMgr();
	MySharedPtr<TimerMgr> getTimerMgr();
	MySharedPtr<FrameTimerMgr> getFrameTimerMgr();
	MySharedPtr<InputMgr> getInputMgr();
	MySharedPtr<MsgRouteNotify> getMsgRouteNotify();
	MySharedPtr<GlobalDelegate> getGlobalDelegate();
	MySharedPtr<GlobalEventCmd> getGlobalEventCmd();

	//MySharedPtr<UMyBluePrintBase> getBPCtx();
	UMyBluePrintBase* getBPCtx();
	FMyNativeObjectReferencer* getNativeObjectReferencer();
	
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
#define GNetCmdNotify GCtx->getNetCmdNotify()
#define GCfg GCtx->getConfig()
#define GPoolSys GCtx->getPoolSys()
#define GResLoadMgr GCtx->getResLoadMgr()

#define GClassAssetInsMgr GCtx->getClassAssetInsMgr()
#define GObjectAssetInsMgr GCtx->getObjectAssetInsMgr()
#define GTextureInsResMgr GCtx->getTextureInsResMgr()
#define GMaterialInsResMgr GCtx->getMaterialInsResMgr()

#define GSandboxPlatformFile GCtx->getSandboxPlatformFile()
#define GMyStreamableManager GCtx->getMyStreamableManager()
#define GDownloadMgr GCtx->getDownloadMgr()
#define GFileSys GCtx->getFileSys()
#define GFileSysSandboxPlatformFile GCtx->getFileSys()->getSandboxPlatformFile()
#define GSystemSetting GCtx->getSystemSetting()
#define GLuaSystem GCtx->getLuaSystem()
#define GSceneEventCB GCtx->getSceneEventCB()
#define GMyLatentActionManager GCtx->getMyLatentActionManager()

#define GSceneSys GCtx->getSceneSys()
#define GSystemTimeData GCtx->getSystemTimeData()
#define GSystemFrameData GCtx->getSystemFrameData()
#define GProcessSys GCtx->getProcessSys()
#define GEngineLoop GCtx->getEngineLoop()
#define GDelayTaskMgr GCtx->getDelayTaskMgr()

#define GTickMgr GCtx->getTickMgr()
#define GTimerMgr GCtx->getTimerMgr()
#define GFrameTimerMgr GCtx->getFrameTimerMgr()
#define GMsgRouteNotify GCtx->getMsgRouteNotify()
#define GInputMgr GCtx->getInputMgr()
#define GMsgRouteNotify GCtx->getMsgRouteNotify()
#define GGlobalDelegate GCtx->getGlobalDelegate()
#define GGlobalEventCmd GCtx->getGlobalEventCmd()

#define GBPCtx GCtx->getBPCtx()
#define GNativeObjectReferencer GCtx->getNativeObjectReferencer()

MY_END_NAMESPACE

#endif				// __Ctx_H