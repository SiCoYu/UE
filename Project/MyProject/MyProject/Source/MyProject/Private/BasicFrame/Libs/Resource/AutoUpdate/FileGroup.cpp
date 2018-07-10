#include "MyProject.h"
#include "FileGroup.h"

MY_BEGIN_NAMESPACE(MyNS)

FileGroup::FileGroup()
{
	this->mCurNum = 0;
	this->mTotalNum = 0;
	this->mCurMemSize = 0;
	this->mTotalMemSize = 0;

	this->mProgressDispatch = new AddOnceEventDispatch();

	this->reset();
}

bool FileGroup::isUpdateSuccess()
{
	return (this->mCurNum == this->mTotalNum &&
		0 == this->mFailedPath.count() &&
		0 == this->mLoadingPath.count());
}

bool FileGroup::isCurEqTotal()
{
	return this->mCurNum == this->mTotalNum;
}

void FileGroup::reset()
{
	this->mCurNum = 0;
	this->mTotalNum = 0;

	this->mLoadingPath.clear();
	this->mLoadedPath.clear();
	this->mFailedPath.clear();
}

void FileGroup::setTotalNum(int value)
{
	this->mTotalNum = value;
}

int FileGroup::getTotalNum()
{
	return this->mTotalNum;
}

void FileGroup::incCurNum()
{
	this->mCurNum += 1;
}

int FileGroup::getCurNum()
{
	return this->mCurNum;
}

// 有正在加载的内容
bool FileGroup::hasLoading()
{
	return this->mLoadingPath.count() > 0;
}

// 有加载失败的
bool FileGroup::hasLoadFailed()
{
	return this->mFailedPath.count() > 0;
}

// 增加更新的文件
void FileGroup::addLoadingPath(std::string path, FileVerInfo fileVerInfo /*, bool isAddTotalNum = false*/)
{
	this->mTotalMemSize += fileVerInfo.mFileSize;

	this->mLoadingPath.add(path);
	this->mUpdatePathDic.add(path, true);    // 开始加载设置加载标志

	//if(isAddTotalNum)
	//{
	//    this->mTotalNum += 1;
	//}

	//this->mProgressDispatch.dispatchEvent(null);
}

void FileGroup::removeLoadingPath(std::string path/*, bool isDecTotalNum = false*/)
{
	FileVerInfo fileVerInfo = Ctx.msInstance.mVersionSys.mServerVer.mABPath2HashDic[path];

	if (null != fileVerInfo)
	{
		this->mCurMemSize += fileVerInfo.mFileSize;
	}

	this->mLoadingPath.remove(path);

	//if (isDecTotalNum)
	//{
	//    this->mTotalNum -= 1;
	//}

	this->mProgressDispatch.dispatchEvent(null);
}

void FileGroup::addLoadedPath(std::string path/*, bool isAddTotalNum = false*/)
{
	this->mLoadedPath.add(path);

	//if (isAddTotalNum)
	//{
	//    this->mTotalNum += 1;
	//}
}

void FileGroup::addFailedPath(std::string path/*, bool isAddTotalNum = false*/)
{
	this->mFailedPath.add(path);
	this->mUpdatePathDic.remove(path);   // 如果加载失败，就是没有更新的资源，需要移除这个更新的资源

	//if (isAddTotalNum)
	//{
	//    this->mTotalNum += 1;
	//}

	//this->mProgressDispatch.dispatchEvent(null);
}

// 获取进度 [0, 100]
int FileGroup::getProgress()
{
	int curNum = this->mLoadedPath.count() + this->mFailedPath.count();
	int totalNum = this->mLoadingPath.count() + this->mLoadedPath.count() + this->mFailedPath.count();

	int progress = 0;

	if (totalNum != 0)
	{
		progress = (int)(((float)curNum / totalNum) * 100);
	}

	return progress;
}

// 获取文件加载内存大小
int FileGroup::getAllNeedUpdateMenSize()
{
	return this->mTotalMemSize;
}

// 获取当前加载的文件大小
int FileGroup::getCurUpdatedMenSize()
{
	return this->mCurMemSize;
}

// 获取加载进度描述
string FileGroup::getProgressDesc()
{
	string ret = "";

	ret = string.Format("{0}M/{1}M", UtilMath.integerWithFract((float)this->mCurMemSize / UtilMath.OneM, 2), UtilMath.integerWithFract((float)this->mTotalMemSize / UtilMath.OneM, 2));

	return ret;
}

// 输出下载详细日志
void FileGroup::logDownloadDetailInfo()
{
	Ctx.msInstance.mLogSys.log(string.Format("FileGroup::logDownloadDetailInfo, mCurNum = {0}, mTotalNum = {1}", this->mCurNum, this->mTotalNum), LogTypeId.eLogAutoUpdate);

	int index = 0;
	int listLen = this->mLoadingPath.count();

	Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** LoadingPath start **********", LogTypeId.eLogAutoUpdate);

	while (index < listLen)
	{
		Ctx.msInstance.mLogSys.log(string.Format("FileGroup::logDownloadDetailInfo, index = {0}, LoadingPath = {1}", index, this->mLoadingPath[index]), LogTypeId.eLogAutoUpdate);

		index += 1;
	}

	Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** LoadingPath end **********", LogTypeId.eLogAutoUpdate);

	index = 0;
	listLen = this->mLoadedPath.count();

	Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** mLoadedPath start **********", LogTypeId.eLogAutoUpdate);

	while (index < listLen)
	{
		Ctx.msInstance.mLogSys.log(string.Format("FileGroup::logDownloadDetailInfo, index = {0}, mLoadedPath = {1}", index, this->mLoadedPath[index]), LogTypeId.eLogAutoUpdate);

		index += 1;
	}

	Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** mLoadedPath end **********", LogTypeId.eLogAutoUpdate);

	index = 0;
	listLen = this->mFailedPath.count();

	Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** mFailedPath start **********", LogTypeId.eLogAutoUpdate);

	while (index < listLen)
	{
		Ctx.msInstance.mLogSys.log(string.Format("FileGroup::logDownloadDetailInfo, index = {0}, mFailedPath = {1}", index, this->mFailedPath[index]), LogTypeId.eLogAutoUpdate);

		index += 1;
	}

	Ctx.msInstance.mLogSys.log("FileGroup::logDownloadDetailInfo, ********** mFailedPath end **********", LogTypeId.eLogAutoUpdate);
}

// 获取当前资源是否更新了
bool FileGroup::isResUpdatedByResPath(string path)
{
	bool ret = false;

	ResRedirectItem resRedirectItem = Ctx.msInstance.mResRedirect.getResRedirectItem(ShaderCollectPath.StartShaderCollect, false);

	if (null != resRedirectItem)
	{
		ret = this->isResUpdatedByABPath(resRedirectItem.mFileVerInfo.mLoadPath);
	}

	return ret;
}

// 获取当前资源是否更新了
bool FileGroup::isResUpdatedByABPath(string path)
{
	bool ret = false;
	this->mUpdatePathDic.tryGetValue(path, out ret);
	return ret;
}

void FileGroup::addProgressHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle)
{
	this->mProgressDispatch.addEventHandle(pThis, handle);
}

void FileGroup::removeProgressHandle(ICalleeObject pThis, MEventDispatchAction<IDispatchObject> handle)
{
	this->mProgressDispatch.removeEventHandle(pThis, handle);
}

MY_END_NAMESPACE