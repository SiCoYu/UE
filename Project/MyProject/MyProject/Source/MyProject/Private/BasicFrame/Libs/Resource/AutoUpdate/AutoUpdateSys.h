#pragma once

#include "AutoUpdateErrorCode.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class FileGroup;
class AddOnceAndCallOnceEventDispatch;
class AutoUpdateErrorInfo;
class FileVerInfo;
class IDispatchObject;

/**
 * @brief 自动更新系统
 */
class AutoUpdateSys : public GObject
{
protected:
	FileGroup* mFileGroup;
    AddOnceAndCallOnceEventDispatch* mOnUpdateEndDispatch;
    AutoUpdateErrorInfo* mAutoUpdateErrorInfo;

public:
	AutoUpdateSys();

	void init();
	void dispose();

	FileGroup* getFileGroup();
	AutoUpdateErrorCode getAutoUpdateErrorCode();
	void setAutoUpdateErrorCode(AutoUpdateErrorCode value);
	AddOnceAndCallOnceEventDispatch* getUpdateEndDispatch();
	void startUpdate();
    // 成功更新
	bool isUpdateSuccess();
    // 成功更新，并且重新下载 Version_P.txt，并且成功更新需要更新的资源文件
	bool isUpdateWebVersionPSuccessAndAllUpdateSuccess();

protected:
	void _checkIsNeedUpdateManifest();
	void loadWebMiniVersion();
	void onWebMiniVerLoadResult(IDispatchObject* dispObj, uint uniqueId);
	void onWebVerLoadResult(IDispatchObject* idspObj, uint uniqueId);

    // 下载基本的 Web 文件失败
protected:
	void _downloadWebMiniFail();
    // 下载 App 文件
	void _downloadApp();

	void _loadAllUpdateFile();
	void _loadOneUpdateFile(std::string path, FileVerInfo* fileInfo);
	void _onLoadEventHandle(IDispatchObject* dispObj, uint uniqueId);
	void _checkUpdateEnd();

public:
	void onUpdateEnd();

    // 是否在更新列表中
protected:
	bool _isIncludeUpdateList(std::string path);
    // 获取无需从服务器更新的文件数量
	int _getExcludeUpdateFileNum();
};

MY_END_NAMESPACE