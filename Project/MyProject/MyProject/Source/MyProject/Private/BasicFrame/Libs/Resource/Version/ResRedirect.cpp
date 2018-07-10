#include "MyProject.h"
#include "ResRedirect.h"

MY_BEGIN_NAMESPACE(MyNS)

ResRedirect::ResRedirect()
{
	this->mOrigPath2ItemDic = MY_NEW MDictionary<string, ResRedirectItem>();
	this->mABPath2ItemDic = MY_NEW MDictionary<string, ResRedirectItem>();
}

void ResRedirect::init()
{

}

void ResRedirect::dispose()
{

}

// 清理之前缓存信息
void ResRedirect::clearCacheInfo()
{
	this->mOrigPath2ItemDic.clear();
	this->mABPath2ItemDic.clear();
}

// 资源是否可以重定向，只有在 Version_S.txt 或者在 Version_P.txt 中的资源才能判断是存在的
bool ResRedirect::canResRedirect(string origPath, bool isABAsset)
{
	bool ret = false;

	ResRedirectItem redirectItem = Ctx.msInstance.mResRedirect.getResRedirectItem(origPath, isABAsset);
	ret = !redirectItem.mFileVerInfo.isNoVerInfo();

	return ret;
}

// isABAsset 是否是 AssetBundles 资源目录
ResRedirectItem ResRedirect::getResRedirectItem(string origPath, bool isABAsset)
{
	ResRedirectItem item = null;
	FileVerInfo fileVerInfo = null;

	if (!isABAsset)
	{
		if (this->mOrigPath2ItemDic.containsKey(origPath))
		{
			item = this->mOrigPath2ItemDic[origPath];
		}
		else
		{
			// 从版本系统中获取
			item = new ResRedirectItem(origPath, (int)ResLoadType.eLoadResource);
			this->mOrigPath2ItemDic[origPath] = item;

			item.mResLoadType = (ResLoadType)Ctx.msInstance.mVersionSys.mLocalVer.getFileVerInfo(origPath, ref fileVerInfo, isABAsset);
			item.mFileVerInfo = fileVerInfo;
		}
	}
	else
	{
		if (this->mABPath2ItemDic.containsKey(origPath))
		{
			item = this->mABPath2ItemDic[origPath];
		}
		else
		{
			// 从版本系统中获取
			item = new ResRedirectItem(origPath, (int)ResLoadType.eLoadStreamingAssets);
			this->mABPath2ItemDic[origPath] = item;

			item.mResLoadType = (ResLoadType)Ctx.msInstance.mVersionSys.mLocalVer.getFileVerInfo(origPath, ref fileVerInfo, isABAsset);
			item.mFileVerInfo = fileVerInfo;
		}
	}

	if (null == item.mFileVerInfo)
	{
		if (MacroDef.ENABLE_LOG)
		{
			Ctx.msInstance.mLogSys.log(string.Format("ResRedirectItem::getResRedirectItem, cannot find load item, origPath = {0}", origPath), LogTypeId.eLogResLoader);
		}

		fileVerInfo = new FileVerInfo();
		fileVerInfo.mOrigPath = origPath;
		fileVerInfo.mResUniqueId = UtilFileIO.getFilePathNoExt(origPath);
		fileVerInfo.mLoadPath = UtilFileIO.getFilePathNoExt(origPath);
		fileVerInfo.mFileMd5 = "error";
		fileVerInfo.mFileSize = 0;

		item.mFileVerInfo = fileVerInfo;
	}
	else
	{
		if (MacroDef.ENABLE_LOG)
		{
			Ctx.msInstance.mLogSys.log(string.Format("ResRedirectItem::getResRedirectItem, find load item, origPath = {0}, mResLoadType = {1}", origPath, item.mResLoadType), LogTypeId.eLogResLoader);
		}
	}

	return item;
}

MY_END_NAMESPACE