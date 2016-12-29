#pragma once

#include "IDispatchObject.h"
#include "ITask.h"
#include "DownloadParam.h"
#include "ResLoadType.h"
#include "ResPackType.h"
#include "RefCountResLoadResultNotify.h"
#include "ResEventDispatch.h"
#include <string>

/**
 * @brief 从网络下载数据
 */
class DownloadItem : public ITask, public IDispatchObject
{
protected:
    char mBytes[128];
    std::string mText;
	std::string mVersion;

	std::string mLocalPath;            // 本地文件系统目录
	std::string mLoadPath;             // 加载目录
	std::string mOrigPath;             // 原始的加载目录
	std::string mLogicPath;            // 逻辑获取的目录
	std::string mResUniqueId;          // 资源 Unique Id
	std::string mDownloadNoVerPath;         // 下载目录，没有版本号
	std::string mDownloadVerPath;         // 下载目录，有版本号

    DownloadType mDownloadType;   // 加载类型
    ResLoadType mResLoadType;
    ResPackType mResPackType;

    RefCountResLoadResultNotify* mRefCountResLoadResultNotify;
    ResEventDispatch* mAllLoadResEventDispatch;    // 事件分发器，这个是记录逻辑的器

    bool mIsWriteFile;
    long mFileLen;

public:
	DownloadItem();

	RefCountResLoadResultNotify* getRefCountResLoadResultNotify();
	void setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value);

	ResEventDispatch* getAllLoadResEventDispatch();
	void setAllLoadResEventDispatch(ResEventDispatch* value);

	virtual void reset();

	std::string getLoadPath();
	void setLoadPath(std::string value);
	std::string getOrigPath();
	void setOrigPath(std::string value);
	DownloadType getDownloadType();
	void setDownloadType(DownloadType value);

	bool hasSuccessLoaded();
	bool hasFailed();

	void setLogicPath(std::string value);
	std::string getLogicPath();
	void setResUniqueId(std::string value);
	std::string getResUniqueId();
	std::string getLoadPath();
    char* getBytes();
	std::string getText();

    virtual void init();
    virtual void failed();
    // 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
    virtual void unload();

    void setLoadParam(DownloadParam* param);
    virtual void load();
    virtual void runTask();
    virtual void handleResult();
    // 加载完成写入本地文件系统
    virtual void writeFile();
};