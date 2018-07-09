#pragma once

#include <string>
#include "MList.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class AddOnceEventDispatch;

/**
 * @brief 一组文件的统计信息
 */
class FileGroup : public GObject
{
protected:
	int mCurNum;          // 当前已经更新的资源数量
	int mTotalNum;        // 总共需要更新的资源数量
	int mCurMemSize;      // 当前资源内存总共大小，单位 byte
	int mTotalMemSize;    // 总共资源内存总共大小，单位 byte

	MList<std::string> mLoadingPath;       // 将要下载
	MList<std::string> mLoadedPath;        // 已经下载成功
	MList<std::string> mFailedPath;        // 下载失败

	MDictionary<std::string, bool> mUpdatePathDic;    // 更新的资源目录

	AddOnceEventDispatch* mProgressDispatch;   // 进度事件分发

public:
	FileGroup()
	{
		this.mCurNum = 0;
		this.mTotalNum = 0;
		this.mCurMemSize = 0;
		this.mTotalMemSize = 0;

		this.mProgressDispatch = new AddOnceEventDispatch();

		this.reset();
	}

	bool isUpdateSuccess()
	{
		return (this.mCurNum == this.mTotalNum &&
			   0 == this.mFailedPath.count() &&
			   0 == this.mLoadingPath.count());
	}

	bool isCurEqTotal()
	{
		return this.mCurNum == this.mTotalNum;
	}

	void reset()
	{
		this.mCurNum = 0;
		this.mTotalNum = 0;

		this.mLoadingPath.clear();
		this.mLoadedPath.clear();
		this.mFailedPath.clear();
	}

	void setTotalNum(int value)
	{
		this.mTotalNum = value;
	}

	int getTotalNum()
	{
		return this.mTotalNum;
	}

	void incCurNum()
	{
		this.mCurNum += 1;
	}

	int getCurNum()
	{
		return this.mCurNum;
	}

	// 有正在加载的内容
	bool hasLoading()
	{
		return this.mLoadingPath.count() > 0;
	}

	// 有加载失败的
	bool hasLoadFailed()
	{
		return this.mFailedPath.count() > 0;
	}

	// 增加更新的文件
	void addLoadingPath(std::string path, FileVerInfo fileVerInfo /*, bool isAddTotalNum = false*/)
	{
		this.mTotalMemSize += fileVerInfo.mFileSize;

		this.mLoadingPath.add(path);
		this.mUpdatePathDic.add(path, true);    // 开始加载设置加载标志

		//if(isAddTotalNum)
		//{
		//    this.mTotalNum += 1;
		//}

		//this.mProgressDispatch.dispatchEvent(null);
	}

	void removeLoadingPath(std::string path/*, bool isDecTotalNum = false*/)
	{
		FileVerInfo fileVerInfo = Ctx.msInstance.mVersionSys.mServerVer.mABPath2HashDic[path];

		if (null != fileVerInfo)
		{
			this.mCurMemSize += fileVerInfo.mFileSize;
		}

		this.mLoadingPath.remove(path);

		//if (isDecTotalNum)
		//{
		//    this.mTotalNum -= 1;
		//}

		this.mProgressDispatch.dispatchEvent(null);
	}

	void addLoadedPath(std::string path/*, bool isAddTotalNum = false*/)
	{
		this.mLoadedPath.add(path);

		//if (isAddTotalNum)
		//{
		//    this.mTotalNum += 1;
		//}
	}

	void addFailedPath(std::string path/*, bool isAddTotalNum = false*/)
	{
		this.mFailedPath.add(path);
		this.mUpdatePathDic.remove(path);   // 如果加载失败，就是没有更新的资源，需要移除这个更新的资源

		//if (isAddTotalNum)
		//{
		//    this.mTotalNum += 1;
		//}

		//this.mProgressDispatch.dispatchEvent(null);
	}

	// 获取进度 [0, 100]
	int getProgress()
	{
		int curNum = this.mLoadedPath.count() + this.mFailedPath.count();
		int totalNum = this.mLoadingPath.count() + this.mLoadedPath.count() + this.mFailedPath.count();

		int progress = 0;

		if (totalNum != 0)
		{
			progress = (int)(((float)curNum / totalNum) * 100);
		}

		return progress;
	}

	// 获取文件加载内存大小
	int getAllNeedUpdateMenSize()
	{
		return this.mTotalMemSize;
	}

	// 获取当前加载的文件大小
	int getCurUpdatedMenSize()
	{
		return this.mCurMemSize;
	}

	// 获取加载进度描述
	string getProgressDesc()
	{
		string ret = "";

		ret = string.Format("{0}M/{1}M", UtilMath.integerWithFract((float)this.mCurMemSize / UtilMath.OneM, 2), UtilMath.integerWithFract((float)this.mTotalMemSize / UtilMath.OneM, 2));

		return ret;
	}

	// 输出下载详细日志
	void logDownloadDetailInfo()
	{
		Ctx.msInstance.mLogSys.log(string.Format("FileGroup::logDownloadDetailInfo, mCurNum = {0}, mTotalNum = {1}", this.mCurNum, this.mTotalNum), LogTypeId.eLogAutoUpdate);

		int index = 0;
		int listLen = this.mLoadingPath.count();

		Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** LoadingPath start **********", LogTypeId.eLogAutoUpdate);

		while (index < listLen)
		{
			Ctx.msInstance.mLogSys.log(string.Format("FileGroup::logDownloadDetailInfo, index = {0}, LoadingPath = {1}", index, this.mLoadingPath[index]), LogTypeId.eLogAutoUpdate);

			index += 1;
		}

		Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** LoadingPath end **********", LogTypeId.eLogAutoUpdate);

		index = 0;
		listLen = this.mLoadedPath.count();

		Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** mLoadedPath start **********", LogTypeId.eLogAutoUpdate);

		while (index < listLen)
		{
			Ctx.msInstance.mLogSys.log(string.Format("FileGroup::logDownloadDetailInfo, index = {0}, mLoadedPath = {1}", index, this.mLoadedPath[index]), LogTypeId.eLogAutoUpdate);

			index += 1;
		}

		Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** mLoadedPath end **********", LogTypeId.eLogAutoUpdate);

		index = 0;
		listLen = this.mFailedPath.count();

		Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** mFailedPath start **********", LogTypeId.eLogAutoUpdate);

		while (index < listLen)
		{
			Ctx.msInstance.mLogSys.log(string.Format("FileGroup::logDownloadDetailInfo, index = {0}, mFailedPath = {1}", index, this.mFailedPath[index]), LogTypeId.eLogAutoUpdate);

			index += 1;
		}

		Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** mFailedPath end **********", LogTypeId.eLogAutoUpdate);
	}

	// 获取当前资源是否更新了
	bool isResUpdatedByResPath(string path)
	{
		bool ret = false;

		ResRedirectItem resRedirectItem = Ctx.msInstance.mResRedirect.getResRedirectItem(ShaderCollectPath.StartShaderCollect, false);

		if (null != resRedirectItem)
		{
			ret = this.isResUpdatedByABPath(resRedirectItem.mFileVerInfo.mLoadPath);
		}

		return ret;
	}

	// 获取当前资源是否更新了
	bool isResUpdatedByABPath(string path)
	{
		bool ret = false;
		this.mUpdatePathDic.tryGetValue(path, out ret);
		return ret;
	}

	void addProgressHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle)
	{
		this.mProgressDispatch.addEventHandle(pThis, handle);
	}

	void removeProgressHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle)
	{
		this.mProgressDispatch.removeEventHandle(pThis, handle);
	}
};

MY_END_NAMESPACE