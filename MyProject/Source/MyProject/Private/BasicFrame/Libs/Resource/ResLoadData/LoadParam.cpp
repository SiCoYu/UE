#include "MyProject.h"
#include "LoadParam.h"
#include "UtilStr.h"
#include "UtilLogic.h"

std::string LoadParam::getPrefabName()
{
	return mPrefabName;
}

std::string LoadParam::getExtName()
{
	return mExtName;
}

std::string LoadParam::getLvlName()
{
	return mLvlName;
}

void LoadParam::resetDefault()          // 将数据清空，有时候上一次调用的时候的参数 m_loaded 还在，结果被认为是这一次的回调了
{
	mLoadEventHandle = nullptr;
	mVersion = "";
	mExtName = "prefab";
	mOrigPath = "";

	mLoadRes = nullptr;
	mLoadInsRes = nullptr;
}

// 解析目录
void LoadParam::resolvePath()
{
	int dotIdx = UtilStr::IndexOf(mPath, ".");
	int slashIdx = UtilStr::LastIndexOf(mPath, "/");

	if (-1 == dotIdx)       // 材质是没有扩展名字的
	{
		mExtName = "";
		mPathNoExt = mPath;

		if (-1 == slashIdx)  // 没有路径，只有一个文件名字
		{
			mPrefabName = mPath;
		}
		else
		{
			mPrefabName = UtilStr::Substring(mPath, slashIdx + 1);
		}
	}
	else
	{
		mExtName = UtilStr::Substring(mPath, dotIdx + 1);
		mPathNoExt = UtilStr::Substring(mPath, 0, dotIdx);

		if (-1 == slashIdx)  // 没有路径，只有一个文件名字
		{
			mPrefabName = UtilStr::Substring(mPath, 0, dotIdx);
		}
		else
		{
			mPrefabName = UtilStr::Substring(mPath, slashIdx + 1, dotIdx - slashIdx - 1);
		}
	}
}

void LoadParam::resolveLevel()
{
	resolvePath();

	int slashIdx = 0;
	if (UtilStr::IsNullOrEmpty(mOrigPath))
	{
		slashIdx = UtilStr::LastIndexOf(mPathNoExt, "/");
		if (slashIdx != -1)
		{
			mLvlName = UtilStr::Substring(mPathNoExt, slashIdx + 1);
		}
		else
		{
			mLvlName = mPathNoExt;
		}
	}
	else        // 如果是打包，需要从原始加载目录获取关卡名字
	{
		mLvlName = UtilLogic::convScenePath2LevelName(mOrigPath);
	}
}