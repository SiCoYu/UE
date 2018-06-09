#ifndef __Prequisites_H
#define __Prequisites_H

/**
 * @brief 全局变量需要的头文件
 * @file Prequisites.h
 */
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "MClassFactory.h"

#include "Ctx.h"
#include "EngineData.h"
#include "INetMgr.h"
#include "UiMgr.h"
#include "UtilEngineWrap.h"
#include "NetMgr.h"
#include "LogSys.h"
#include "ShareData.h"
#include "NetCmdNotify.h"
#include "Config.h"
#include "PoolSys.h"

#include "ResLoadMgr.h"
#include "ClassAssetInsMgr.h"
#include "ObjectAssetInsMgr.h"
#include "TextureInsResMgr.h"
#include "MaterialInsResMgr.h"
#include "MyStreamableManager.h"
#include "DownloadMgr.h"
#include "MFileSys.h"
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


// 内存
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"

#include "MyNativeObjectReferencer.h"

#endif