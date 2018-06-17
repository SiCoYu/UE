#pragma once

#include <string>

#include "GObject.h"
#include "IDispatchObject.h"
#include "TypeDef.h"
#include "EventDispatchDelegate.h"
#include "DownloadParam.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "CoreInc.h"
#include "DownloadType.h"
#include "ResLoadPriority.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ResLoadState;
class ResEventDispatch;

/**
 * @brief 资源加载器
 */
class AuxLoaderBase : public GObject, public IDispatchObject
{
	M_DECLARE_CLASS(AuxLoaderBase, GObject)

protected:
	ResLoadState* mResLoadState;      // 资源加载状态
    std::string mPrePath;      // 之前加载的资源目录
	std::string mPath;         // 加载的资源目录
    ResEventDispatch* mResEventDispatch;              // 事件分发器
	ResEventDispatch* mProgressEventDispatch;
    bool mIsInvalid;      // 加载器是否无效
	std::string mInitPath;     // 初始化目录
	ResLoadPriority mResLoadPriority;

public:
	AuxLoaderBase();

protected:
	void reset();

public:
	virtual void init();
	virtual void dispose();
	bool hasSuccessLoaded();
	bool hasFailed();
    // 加载成功或者加载失败
	bool hasLoadEnd();
    // 是否需要卸载资源
	bool needUnload(std::string path);
	void setPath(std::string path);
	void updatePath(std::string path);
	bool isInvalid();
	virtual std::string getOrigPath();

	// 真正的开始加载
	void onStartLoad();
	// 资源加载完成成功
	void onLoaded();
	// 加载失败
	void onFailed();
	// 开始实例化
	void onStartIns();
	// 实例化完成成功
	void onSuccessIns();
	// 实例化失败
	void onInsFailed();

	virtual void onProgressEventHandle(IDispatchObject* dispObj, uint eventId = 0);

protected:
	void addEventHandle(EventDispatchDelegate evtHandle = nullptr);

	virtual void syncLoad(
		std::string path, 
		EventDispatchDelegate evtHandle = nullptr,
		EventDispatchDelegate progressHandle = nullptr
	);

	virtual void asyncLoad(
		std::string path, 
		EventDispatchDelegate evtHandle,
		EventDispatchDelegate progressHandle = nullptr
	);

	virtual void download(
		std::string origPath, 
		EventDispatchDelegate handle = nullptr,
		long fileLen = 0, 
		bool isWriteFile = true, 
		int downloadType = (int)DownloadType::eHttpWeb
	);

	virtual void unload();
};

MY_END_NAMESPACE